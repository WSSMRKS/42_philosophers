#!/bin/bash

# Compile the program
make

# Function to count the number of actions (eating, sleeping, thinking) for each philosopher
count_actions() {
    log_file=$1
    echo "Number of eats in $log_file:"
    x=1; while [ $x -le 10 ]; do echo "Philosopher $x eating: $(grep "$x is eating" $log_file | wc -l)"; x=$((x+1)); done

    echo "Number of sleeps in $log_file:"
    x=1; while [ $x -le 10 ]; do echo "Philosopher $x sleeping: $(grep "$x is sleeping" $log_file | wc -l)"; x=$((x+1)); done

    echo "Number of thinks in $log_file:"
    x=1; while [ $x -le 10 ]; do echo "Philosopher $x thinking: $(grep "$x is thinking" $log_file | wc -l)"; x=$((x+1)); done
}

# Test 1: Single philosopher, should die (log1)
./philo 1 800 200 200 >log1
echo "Test 1: Philosopher should die"
count_actions log1

# Test 2: 4 philosophers, one should die (log2)
./philo 4 310 200 100 >log2
echo "Test 2: Philosopher should die"
count_actions log2

# Test 3: 4 philosophers, one should die (log3)
./philo 4 200 205 200 >log3
echo "Test 3: Philosopher should die"
count_actions log3

# Test 4: 5 philosophers, no one should die, stop after 7 eats (log4)
./philo 5 800 200 200 7 >log4
echo "Test 4: Simulation should stop after 7 eats"
count_actions log4

# Test 5: 4 philosophers, no one should die, stop after 10 eats (log5)
./philo 4 410 200 200 10 >log5
echo "Test 5: Simulation should stop after 10 eats"
count_actions log5

# Test 6-10: Invalid parameters, should not run (log6-log10)
echo "Test 6-10: Invalid parameters, should not crash"
./philo -5 600 200 200 >log6 2>&1
./philo 4 -5 200 200 >log7 2>&1
./philo 4 600 -5 200 >log8 2>&1
./philo 4 600 200 -5 >log9 2>&1
./philo 4 600 200 200 -5 >log10 2>&1

echo "Log 6: Error output"
grep "Error" log6

echo "Log 7: Error output"
grep "Error" log7

echo "Log 8: Error output"
grep "Error" log8

echo "Log 9: Error output"
grep "Error" log9

echo "Log 10: Error output"
grep "Error" log10

# Test 11-16: Use timeout to stop the simulation after 50 seconds (log11-log16)
echo "Test 11-16: Simulations running for 50 seconds each"
timeout 50s ./philo 5 800 200 200 200 >log11
echo 1/6 done
timeout 50s ./philo 5 600 150 150 50 >log12
echo 2/6 done
timeout 50s ./philo 4 410 200 200 50 >log13
echo 3/6 done
timeout 50s ./philo 100 800 200 200 50 >log14
echo 4/6 done
timeout 50s ./philo 105 800 200 200 50 >log15
echo 5/6 done
timeout 50s ./philo 200 800 200 200 50 >log16
echo 6/6 done

# Display action counts for tests using timeout
count_actions log11
count_actions log12
count_actions log13
count_actions log14
count_actions log15
count_actions log16

echo "Tests completed"
