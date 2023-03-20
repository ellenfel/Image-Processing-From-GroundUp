set terminal png size 1300,800


set output 'OUTPUT.png'

set size 1,1
set multiplot

set size 0.5,0.5

set origin 0,0
plot 'input_signal.dat' with lines lc rgb 'blue'

set origin 0.5,0
p 'impulse_rsp.dat' with lines lc rgb 'red'

set origin 0,0.5
plot 'output_signal.dat'  with lines lc rgb 'blue'
