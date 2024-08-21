T9Predictor
===========

Library for create dictionaries to predict words based on letter frequency in the training data.

The predictor will parse a text file, disregard non-alphabetical characters and case, and create a tree with word counts.

On giving the predictor n letter groups, each representing the pool of potential letters for the 1st, 2nd..nth letter, it will return a list of possible words from the training data, ordered by decreasing frequency of occurrence in the training data.

Build
-----

Builds the library and an example program.

$: mkdir build && cd build
$: cmake ..
$: cmake --build .

Example usage
-------------

 $: ./Debug/predictor.exe example_training_data.txt ghi mno mno def
Parsing training data..Done
done.
Adding group: ghi
Adding group: mno
Adding group: mno
Adding group: def
Predicting..done.
Predictions:
good