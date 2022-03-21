# RR

<h3> how to use </h3>

<h4> BUILD </h4>

<pre>
  mkdir build
  cd build 
  cmake .. 
  make
</pre>

<h4> EXECUTE </h4>
<pre>
  touch processes.txt
  ./main
</pre>

<h3> processes.txt file format <h3>
  
<pre>5    144  8    20   5
200  342  10   10   1
1500 153  5    20   5
20   464  1    3    2
2500 515  3    1    3 </pre>

<p> TIME &nbsp; PID &nbsp; RUN &nbsp; I/O &nbsp; REPEAT </p>
  
<h3> pseudocode of process execution <h3>
<pre>while (there’s another (RUN, I/O, REPEAT) phase for process PID) loop
  for I in 1..REPEAT loop
    do compute for RUN time units
    do I/O for I/O time units
  end loop
  if (this is the last phase) then
    do compute for RUN time units
  end if
end loop</pre>

<p> results will be stored at result.txt in the current directory </p>
