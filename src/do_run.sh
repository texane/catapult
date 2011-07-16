#!/usr/bin/env sh

PLOT_CMD="gnuplot -e \""

[ -d ../dat ] || mkdir ../dat ;

FU='plot' ;
for a in 10 20 30 50 60 70 80; do
    ./a.out $a > ../dat/out.$a ;
    PLOT_CMD="$PLOT_CMD $FU '../dat/out.$a' with lines;"
    FU='replot' ;
done ;

PLOT_CMD="$PLOT_CMD pause-1; \"" ;

sh -c "$PLOT_CMD" ;
