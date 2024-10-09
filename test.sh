#!/bin/bash

make
./philo 1 800 200 200 >log1		#a philo should die
grep eating:
x=1; while [ $x -le 10 ]; do grep "$x is eating" log1 | wc -l; x=$((x+1)); done
grep sleeping:
x=1; while [ $x -le 10 ]; do grep "$x is sleeping" log1 | wc -l; x=$((x+1)); done
grep thinking:
x=1; while [ $x -le 10 ]; do grep "$x is thinking" log1 | wc -l; x=$((x+1)); done
./philo 4 310 200 100 >log2		#a philo should die
./philo 4 200 205 200 >log3		#a philo should die
./philo 5 800 200 200 7 >log4	#no one should die, simulation should stop after 7 eats
./philo 4 410 200 200 10 >log5	#no one should die, simulation should stop after 10 eats
./philo -5 600 200 200 >log6			#should error and not run (no crashing)
./philo 4 -5 200 200 >log7			#should error and not run (no crashing)
./philo 4 600 -5 200 >log8			#should error and not run (no crashing)
./philo 4 600 200 -5 >log9		#should error and not run (no crashing)
./philo 4 600 200 200 -5 >log10		#should error and not run (no crashing)
timeout 50s ./philo 5 800 200 200 200 >log11		#no one should die, simulation should stop after 50 seconds
timeout 50s ./philo 5 600 150 150 50 >log12		#no one should die, simulation should stop after 50 seconds
timeout 50s ./philo 4 410 200 200 50 >log13		#no one should die, simulation should stop after 50 seconds
timeout 50s ./philo 100 800 200 200 50 >log14		#no one should die, simulation should stop after 50 seconds
timeout 50s ./philo 105 800 200 200 50 >log15		#no one should die, simulation should stop after 50 seconds
timeout 50s ./philo 200 800 200 200 50 >log16		#no one should die, simulation should stop after 50 seconds