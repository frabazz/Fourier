(gdb) b fourier.cpp:11
Breakpoint 1 at 0x12a2: file fourier.cpp, line 11.
(gdb) run
Starting program: /home/buzz/Desktop/fourier/src/math/a.out 

This GDB supports auto-downloading debuginfo from the following URLs:
  <https://debuginfod.archlinux.org>
Enable debuginfod for this session? (y or [n]) n
Debuginfod has been disabled.
To make this setting permanent, add 'set debuginfod enabled off' to .gdbinit.
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/libthread_db.so.1".

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.
Fatal glibc error: malloc.c:2599 (sysmalloc): assertion failed: (old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)

Program received signal SIGABRT, Aborted.
0x00007ffff7a87194 in ?? () from /usr/lib/libc.so.6
(gdb) backtrace
#0  0x00007ffff7a87194 in ?? () from /usr/lib/libc.so.6
#1  0x00007ffff7a33d70 in raise () from /usr/lib/libc.so.6
#2  0x00007ffff7a1b4c0 in abort () from /usr/lib/libc.so.6
#3  0x00007ffff7a1c3c2 in ?? () from /usr/lib/libc.so.6
#4  0x00007ffff7a2be08 in ?? () from /usr/lib/libc.so.6
#5  0x00007ffff7a940da in ?? () from /usr/lib/libc.so.6
#6  0x00007ffff7a95092 in ?? () from /usr/lib/libc.so.6
#7  0x00007ffff7a95ac2 in malloc () from /usr/lib/libc.so.6
#8  0x00007ffff7a6f1d6 in _IO_file_doallocate () from /usr/lib/libc.so.6
#9  0x00007ffff7a7e574 in _IO_doallocbuf () from /usr/lib/libc.so.6
#10 0x00007ffff7a7c628 in _IO_file_overflow () from /usr/lib/libc.so.6
#11 0x00007ffff7a7d14f in _IO_file_xsputn () from /usr/lib/libc.so.6
#12 0x00007ffff7a708a2 in fwrite () from /usr/lib/libc.so.6
#13 0x00007ffff7d34b75 in std::basic_streambuf<char, std::char_traits<char> >::sputn (
    __n=<optimized out>, __s=<optimized out>, 
    this=0x7ffff7e72d60 <__gnu_internal::buf_cout_sync>)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/streambuf:457
#14 std::ostreambuf_iterator<char, std::char_traits<char> >::_M_put (__len=<optimized out>, 
    __ws=<optimized out>, this=<synthetic pointer>)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/streambuf_iterator.h:327
#15 std::__write<char> (__len=<optimized out>, __ws=<optimized out>, __s=...)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/locale_facets.h
:124                                                                                            
#16 std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long> (this=<optimized out>, __s=..., __io=..., __fill=<optimized out>, __v=<optimized out>)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/locale_facets.tcc:951 
#17 0x00007ffff7d4413b in std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::put (__v=0, __fill=<optimized out>, __io=..., __s=..., 
    this=0x7ffff7e74690 <(anonymous namespace)::num_put_c>)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/locale_facets.h
:2399                                                                                           
#18 std::basic_ostream<char, std::char_traits<char> >::_M_insert<long> (
    this=0x55555555a080 <std::cout@GLIBCXX_3.4>, __v=0)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/ostream.tcc:78
#19 0x00005555555553e7 in FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:23
#20 0x0000555555555546 in main (argc=1, argv=0x7fffffffdbf8) at fourier.cpp:32
(gdb) kill
Kill the program being debugged? (y or n) y
[Inferior 1 (process 18510) killed]
(gdb) b 22
Breakpoint 2 at 0x555555555392: file fourier.cpp, line 22.
(gdb) run
Starting program: /home/buzz/Desktop/fourier/src/math/a.out 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/libthread_db.so.1".

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) 
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) 
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) 
Continuing.
buzz:math (main*) $ g++ -g fourier.cpp
buzz:math (main*) $ ./a.out
0 1 0 0 4 5 0 0 
buzz:math (main*) $ g++ -g fourier.cpp
buzz:math (main*) $ ./a.out
0 1 2147483648 2147483648 1073741824 1073741824 3221225472 3221225472 
buzz:math (main*) $ g++ -g fourier.cpp
buzz:math (main*) $ ./a.out           
0 2147483648 1073741824 3221225472 536870912 2684354560 1610612736 3758096384 
buzz:math (main*) $ g++ -g fourier.cpp
fourier.cpp:10:37: warning: character constant too long for its type
   10 | To make this setting permanent, add 'set debuginfod enabled off' to .gdbinit.
      |                                     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
fourier.cpp:58:5: error: "0x00007ffff7a87194" is not a valid filename
   58 | #0  0x00007ffff7a87194 in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:59:5: error: "0x00007ffff7a33d70" is not a valid filename
   59 | #1  0x00007ffff7a33d70 in raise () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:60:5: error: "0x00007ffff7a1b4c0" is not a valid filename
   60 | #2  0x00007ffff7a1b4c0 in abort () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:61:5: error: "0x00007ffff7a1c3c2" is not a valid filename
   61 | #3  0x00007ffff7a1c3c2 in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:62:5: error: "0x00007ffff7a2be08" is not a valid filename
   62 | #4  0x00007ffff7a2be08 in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:63:5: error: "0x00007ffff7a940da" is not a valid filename
   63 | #5  0x00007ffff7a940da in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:64:5: error: "0x00007ffff7a95092" is not a valid filename
   64 | #6  0x00007ffff7a95092 in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:65:5: error: "0x00007ffff7a95ac2" is not a valid filename
   65 | #7  0x00007ffff7a95ac2 in malloc () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:66:5: error: "0x00007ffff7a6f1d6" is not a valid filename
   66 | #8  0x00007ffff7a6f1d6 in _IO_file_doallocate () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:67:5: error: "0x00007ffff7a7e574" is not a valid filename
   67 | #9  0x00007ffff7a7e574 in _IO_doallocbuf () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
buzz:math (main*) $ g++ fourier.cpp   
fourier.cpp:10:37: warning: character constant too long for its type
   10 | To make this setting permanent, add 'set debuginfod enabled off' to .gdbinit.
      |                                     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
fourier.cpp:58:5: error: "0x00007ffff7a87194" is not a valid filename
   58 | #0  0x00007ffff7a87194 in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:59:5: error: "0x00007ffff7a33d70" is not a valid filename
   59 | #1  0x00007ffff7a33d70 in raise () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:60:5: error: "0x00007ffff7a1b4c0" is not a valid filename
   60 | #2  0x00007ffff7a1b4c0 in abort () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:61:5: error: "0x00007ffff7a1c3c2" is not a valid filename
   61 | #3  0x00007ffff7a1c3c2 in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:62:5: error: "0x00007ffff7a2be08" is not a valid filename
   62 | #4  0x00007ffff7a2be08 in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:63:5: error: "0x00007ffff7a940da" is not a valid filename
   63 | #5  0x00007ffff7a940da in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:64:5: error: "0x00007ffff7a95092" is not a valid filename
   64 | #6  0x00007ffff7a95092 in ?? () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:65:5: error: "0x00007ffff7a95ac2" is not a valid filename
   65 | #7  0x00007ffff7a95ac2 in malloc () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:66:5: error: "0x00007ffff7a6f1d6" is not a valid filename
   66 | #8  0x00007ffff7a6f1d6 in _IO_file_doallocate () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
fourier.cpp:67:5: error: "0x00007ffff7a7e574" is not a valid filename
   67 | #9  0x00007ffff7a7e574 in _IO_doallocbuf () from /usr/lib/libc.so.6
      |     ^~~~~~~~~~~~~~~~~~
buzz:math (main*) $ cat fourier.cpp        
(gdb) b fourier.cpp:11             
Breakpoint 1 at 0x12a2: file fourier.cpp, line 11.
(gdb) run
Starting program: /home/buzz/Desktop/fourier/src/math/a.out 

This GDB supports auto-downloading debuginfo from the following URLs:
  <https://debuginfod.archlinux.org>
Enable debuginfod for this session? (y or [n]) n
Debuginfod has been disabled.
To make this setting permanent, add 'set debuginfod enabled off' to .gdbinit.
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/libthread_db.so.1".

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.

Breakpoint 1, FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:11
11          if (j > i) {
(gdb) c
Continuing.
Fatal glibc error: malloc.c:2599 (sysmalloc): assertion failed: (old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)

Program received signal SIGABRT, Aborted.
0x00007ffff7a87194 in ?? () from /usr/lib/libc.so.6
(gdb) backtrace
#0  0x00007ffff7a87194 in ?? () from /usr/lib/libc.so.6
#1  0x00007ffff7a33d70 in raise () from /usr/lib/libc.so.6
#2  0x00007ffff7a1b4c0 in abort () from /usr/lib/libc.so.6
#3  0x00007ffff7a1c3c2 in ?? () from /usr/lib/libc.so.6
#4  0x00007ffff7a2be08 in ?? () from /usr/lib/libc.so.6
#5  0x00007ffff7a940da in ?? () from /usr/lib/libc.so.6
#6  0x00007ffff7a95092 in ?? () from /usr/lib/libc.so.6
#7  0x00007ffff7a95ac2 in malloc () from /usr/lib/libc.so.6
#8  0x00007ffff7a6f1d6 in _IO_file_doallocate () from /usr/lib/libc.so.6
#9  0x00007ffff7a7e574 in _IO_doallocbuf () from /usr/lib/libc.so.6
#10 0x00007ffff7a7c628 in _IO_file_overflow () from /usr/lib/libc.so.6
#11 0x00007ffff7a7d14f in _IO_file_xsputn () from /usr/lib/libc.so.6
#12 0x00007ffff7a708a2 in fwrite () from /usr/lib/libc.so.6
#13 0x00007ffff7d34b75 in std::basic_streambuf<char, std::char_traits<char> >::sputn (
    __n=<optimized out>, __s=<optimized out>, 
    this=0x7ffff7e72d60 <__gnu_internal::buf_cout_sync>)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/streambuf:457
#14 std::ostreambuf_iterator<char, std::char_traits<char> >::_M_put (__len=<optimized out>, 
    __ws=<optimized out>, this=<synthetic pointer>)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/streambuf_iterator.h:327
#15 std::__write<char> (__len=<optimized out>, __ws=<optimized out>, __s=...)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/locale_facets.h
:124                                                                                            
#16 std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long> (this=<optimized out>, __s=..., __io=..., __fill=<optimized out>, __v=<optimized out>)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/locale_facets.tcc:951 
#17 0x00007ffff7d4413b in std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::put (__v=0, __fill=<optimized out>, __io=..., __s=..., 
    this=0x7ffff7e74690 <(anonymous namespace)::num_put_c>)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/locale_facets.h        
:2399                                                                                           
#18 std::basic_ostream<char, std::char_traits<char> >::_M_insert<long> (
    this=0x55555555a080 <std::cout@GLIBCXX_3.4>, __v=0)
    at /usr/src/debug/gcc/gcc-build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/ostream.tcc:78
#19 0x00005555555553e7 in FFT (samples=std::vector of length 0, capacity 0) at fourier.cpp:23
#20 0x0000555555555546 in main (argc=1, argv=0x7fffffffdbf8) at fourier.cpp:32
(gdb) kill
Kill the program being debugged? (y or n) y
[Inferior 1 (process 18510) killed]
(gdb) b 22
Breakpoint 2 at 0x555555555392: file fourier.cpp, line 22.
buzz:math (main*) $ ./a.out
0 2147483648 1073741824 3221225472 536870912 2684354560 1610612736 3758096384 
buzz:math (main*) $ g++ -g fourier.cpp
buzz:math (main*) $ ./a.out           
0 2147483648 1073741824 3221225472 536870912 2684354560 1610612736 3758096384 
buzz:math (main*) $ g++ -g fourier.cpp
buzz:math (main*) $ ./a.out           
0 4 2 6 1 5 3 7 
buzz:math (main*) $ g++ -g fourier.cpp
buzz:math (main*) $ ./a.out
Fatal glibc error: malloc.c:2599 (sysmalloc): assertion failed: (old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)
[1]    20278 IOT instruction (core dumped)  ./a.out
buzz:math (main*) $ g++ -g fourier.cpp
buzz:math (main*) $ ./a.out           
4
buzz:math (main*) $ ./a.out           
3
(0,0) (4,0) (2,0) (6,0) (1,0) (5,0) (3,0) (7,0) 
(0,0) + op(4,0)
(2,0) + op(6,0)
(1,0) + op(5,0)
(3,0) + op(7,0)
(8,0) (4,0) (14,0) (6,0) (11,0) (5,0) (17,0) (7,0) 
(8,0) + op(14,0)
(11,0) + op(17,0)
(36,0) (4,0) (14,0) (6,0) (45,0) (5,0) (17,0) (7,0) 
(36,0) + op(45,0)
(126,0) (4,0) (14,0) (6,0) (45,0) (5,0) (17,0) (7,0) 

buzz:math (main*) $ g++ -g fourier.cpp
buzz:math (main*) $ ./a.out           
3
(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) 

buzz:math (main*) $ python3 test.py            
python3: can't open file '/home/buzz/Desktop/fourier/src/math/test.py': [Errno 2] No such file 
or directory
buzz:math (main*) $ 
