#!/bin/sh

ID=`basename $1 .log`
grep -r "Latency" $1 | cut -d ' ' -f 6 | sed "s/'//g" | gnuplot -e "set term png; set yrange [0:4000000]; set ylabel 'latency [ns]'; set output '${ID}.png'; set title '2MB pubsub latency (${ID})'; plot '< cat -' notitle"

