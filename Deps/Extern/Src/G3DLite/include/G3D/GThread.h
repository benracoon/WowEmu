/** 
  @file GThread.h
 
  @created 2005-09-22
  @edited  2010-09-10

 */

#ifndef G3D_GThread_h
#define G3D_GThread_h

#include "G3D/platform.h"
#include "G3D/ReferenceCount.h"
#include "G3D/ThreadSet.h"
#include "G3D/Vector2int32.h"
#include "G3D/SpawnBehavior.h"
#include <string>

#ifndef G3D_WIN32
#   include <pthread.h>
#   include <signal.h>
#endif


namespace G3D {
        
typedef ReferenceCountedPointer<class GThread> GThreadRef;

/**
 Platform independent thread implementation.  You can either subclass and 
 override GThread::threadMain or call the create method with a method.

 Beware of reference counting and threads.  If circular references exist between
 GThread subclasses then neither class will ever be deallocated.  Also, 
 dropping all pointers (and causing deallocation) of a GThread does NOT 
 stop the underlying process.

 \sa G3D::GMutex, G3D::Spinlock, G3D::AtomicInt32, G3D::ThreadGroup
*/
class GThread : public ReferenceCountedObject {
private:
    // "Status" is a reserved work on FreeBSD
    enum GStatus {STATUS_CREATED, STATUS_STARTED, STATUS_RUNNING, STATUS_COMPLETED};

    // Not implemented on purpose, don't use
    GThread(const GThread &);
    GThread& operator=(const GThread&);
    bool operator==(const GThread&);

#ifdef G3D_WIN32
    static DWORD WINAPI internalThreadProc(LPVOID param);
#else
    static void* internalThreadProc(void* param);
#endif //G3D_WIN32

    volatile GStatus     m_status;

    // Thread handle to hold HANDLE and pthread_t
#ifdef G3D_WIN32
    HANDLE              m_handle;
    HANDLE              m_event;
#else
    pthread_t           m_handle;
#endif //G3D_WIN32

    std::string         m_name;

protected:

    /** Overriden by the thread implementor */
    virtual void threadMain() = 0;

    /** Returns System::numCores(); put here to break a dependence on System.h */
    static int numCores();

    template<class Class>
    static void runConcurrently2DHelper
    (const Vector2int32& start, 
     const Vector2int32& upTo, 
     Class*              object,
     void (Class::*method1)(int x, int y),
     void (Class::*method2)(int x, int y, int threadID),
     int                 maxThreads) {
        /** For use by runConcurrently2D. Designed for arbitrary iteration, although only used for
            interlaced rows in the current implementation. */
        class Worker : public GThread {
        public:
            /** Start for this thread, which differs from the others */
            const int                 threadID;
            const Vector2int32        start;
            const Vector2int32        upTo;
            const Vector2int32        stride;
            Class*                    object;
            void             (Class::*method1)(int x, int y);
            void             (Class::*method2)(int x, int y, int threadID);
            
            Worker(int                 threadID,
                   const Vector2int32& start, 
                   const Vector2int32& upTo, 
                   Class*              object,
                   void (Class::*method1)(int x, int y),
                   void (Class::*method2)(int x, int y, int threadID),
                   const Vector2int32& stride) : 
                GThread("runConcurrently2D worker"),
                threadID(threadID),
                start(start),
                upTo(upTo), 
                stride(stride),
                object(object), 
                method1(method1),
                method2(method2) {}
            
            virtual void threadMain() {
                for (int y = start.y; y < upTo.y; y += stride.y) {
                    // Run whichever method was provided
                    if (method1) {
                        for (int x = start.x; x < upTo.x; x += stride.x) {
                            (object->*method1)(x, y);
                        }
                    } else {
                        for (int x = start.x; x < upTo.x; x += stride.x) {
                            (object->*method2)(x, y, threadID);
                        }
                    }
                }
            }
        };
        
        // Create a group of threads
        if (maxThreads == NUM_CORES) {
            maxThreads = numCores();
        }

        const int numRows = upTo.y - start.y;
        const int numThreads = min(maxThreads, numRows);
        const Vector2int32 stride(1, numThreads);
        ThreadSet threadSet;
        for (int t = 0; t < numThreads; ++t) {
            threadSet.insert(new Worker(t, start + Vector2int32(0, t), upTo, object, method1, method2, stride));
        }

        // Run the threads, reusing the current thread and blocking until
        // all complete
        threadSet.start(USE_CURRENT_THREAD);
        threadSet.waitForCompletion();
    }

public:
    typedef ReferenceCountedPointer<class GThread> Ref;

    GThread(const std::string& name);

    virtual ~GThread();

    /** Constructs a basic GThread without requiring a subclass.

        @param proc The global or static function for the threadMain() */
    static GThreadRef create(const std::string& name, void (*proc)(void*), void* param = NULL);

    /** Starts the thread and executes threadMain().  Returns false if
       the thread failed to start (either because it was already started
       or because the OS refused).
       
       @param behavior If USE_CURRENT_THREAD, rather than spawning a new thread, this routine
       runs threadMain on the current thread.
       */
    bool start(SpawnBehavior behavior = USE_NEW_THREAD);

    /** Terminates the thread without notifying or
        waiting for a cancelation point. */
    void terminate();

    /**
        Returns true if threadMain is currently executing.  This will
        only be set when the thread is actually running and might not
        be set when start() returns. */
    bool running() const;

    /** True after start() has been called, even through the thread
        may have already completed(), or be currently running().*/
    bool started() const;

    /** Returns true if the thread has exited. */
    bool completed() const;

    /** Waits for the thread to finish executing. */
    void waitForCompletion();

    /** Returns thread name */
    const std::string& name() {
        return m_name;
    }

    /** For backwards compatibility to G3D 8.xx */
    static const SpawnBehavior USE_CURRENT_THREAD = G3D::USE_CURRENT_THREAD;
    /** For backwards compatibility to G3D 8.xx */
    static const SpawnBehavior USE_NEW_THREAD = G3D::USE_NEW_THREAD;

    enum {
        /** Tells GThread::runConcurrently() and GThread::runConcurrently2D() to
            use System::numCores() threads.*/
        NUM_CORES = -100
    };
    
    /** 
        Iterates over a 2D region using multiple threads and blocks
        until all threads have completed.

        Evaluates \a object->\a method(\ax, \ay) for every 
        <code>start.x <= x < upTo.x</code> and 
        <code>start.y <= y < upTo.y</code>.  Iteration is row major,
        so each thread can expect to see successivly increasing x values.

        \param maxThreads Maximum number of threads to use.  By default at
        most one thread per processor core will be used.

        Example:
        \code
        class RayTracer {
        public:
        
  	void trace(const Vector2int32& pixel) {
        ...
	}

	void traceAll() {
        GThread::runConcurrently2D(Vector2int32(0,0), Vector2int32(w,h), this, &RayTracer::trace);
	}
        };
        \endcode
    */
    template<class Class>
    static void runConcurrently2D
    (const Vector2int32& start, 
     const Vector2int32& upTo, 
     Class*              object,
     void (Class::*method)(int x, int y),
     int                 maxThreads = NUM_CORES) {
        runConcurrently2DHelper(start, upTo, object, method, static_cast<void (Class::*)(int, int, int)>(NULL), maxThreads);
    }

    /** Like the other version of runConcurrently2D, but tells the
        method the thread index that it is running on.  That enables
        the caller to manage per-thread state.
    */
    template<class Class>
    static void runConcurrently2D
    (const Vector2int32& start, 
     const Vector2int32& upTo, 
     Class*              object,
     void (Class::*method)(int x, int y, int threadID),
     int                 maxThreads = NUM_CORES) {
        runConcurrently2DHelper(start, upTo, object, static_cast<void (Class::*)(int, int)>(NULL), method, maxThreads);
    }

};


} // namespace G3D

#endif //G3D_GTHREAD_H
