set terminal pngcairo size 800,600
set output 'weight_trend.png'
set title 'Weight Trend for Kenny'
set xlabel 'Log Day'
set ylabel 'Weight (lbs)'
set grid
plot 'weight_data.txt' using 1:2 with linespoints title 'Weight Progress'
