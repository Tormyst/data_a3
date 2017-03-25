# Assignment 5: Naive Bayes Classifier Implementation
## Implementation by Raphael

This project was created to spec for data mining class.

## Setup
A cmake file has been included which provides a default command to build the program.
For simple use of this cmake project, a makefile has been provided:
```bash
make
```
Although, it is advised to use cmake to configure the project as you would like.  
The makefile will create for you a symbolic link to the created target file.  

## Running

In the build folder you may find the executable **data_a5**.  
A symbolic link has been provided in the top level directory called  **ass5**.  
The program takes in **2**, or **3** arguments.

* A Data File
* A file containing test values
* A target header in said data file (Optional, with interactive menu if left out.)

Running this regularly requires putting this in the PATH variable, or can be run by giving the path.  In most cases the easiest form of this is to append `./` to the beinging of the path name.

```
./ass5 <Data File> <Test File> [<Classifier Target>]
```

To bring up this information, simply use the command:
```
./ass5 -h
```

This implementation will calculate values based on the log of the probabilities in the hopes of making the results better with low probability values. 
 
In addition M values were added to prevent 0% values from resulting in negative infinity values.  

Cleaning the data files is left to the user, if a proper csv file would want to be used and cleaned, such a program would be easy to script and is may be customised based on the noise expected. 
As a result of this uncertainty, the task of cleaning data files for use is left as an exercise for the user.

## Design

### File structure
There are two folders of files, include and src.  Like many C and C++ project, an individual .h file is provided for every .cpp file, excluding main.

The .h files will hopefully serve as a guide to the .cpp files.

I will highlight some functions that may not have as clear uses.

Some files were not removed from the last assignment.  They are included because removing them was not found to be needed.

#### main
Provides the main function to run the program, checks for input value ranges.

#### IOfunctions
Provides the input and output functions.

* readCSV: the input function that returns a database object.  This is also where the test data is read in and the interactive reading of the target is done.
* prittyPrintNaiveBayes: the output function that outputs the table, and the accuracy.

#### database
Stores values read in from a dataset.  Can check the data set for frequencies that comply with a frequent set,
create the initial frequent sets from the dataset.

* encode takes in a string and a column number.  This is used to encode that string as an integer, for faster use.
* decode takes a pair of integers, and gives back the original string.
* setCount takes in a frequentSet and sets the value of it's frequency to the correct value.
* createDataset seeing as many tables need to be used, the createDataset function pulls out a table from the database for ues when recombining.
* createTestDataset is for the test set, but is essentialy the same.

#### frequentSet
Used as a way of searching the database thanks to the structure built for apriori.

#### NaiveBayes
Creates and uses the Naive Bayes table.  

* Setup create the table.
* Predict returns the value of the target based on the table.  

#### rule
Not used here.

#### apriori
Not used here.

###id3
not used here.

### Function 
Now, there are quite a few function calls in this program, so I will provide a simplified view to the important highlights.

* main()
    * IOfunctions->readCSV()                   // Reading in data.
        * database->addData()                  // Read in each line
            * database->encode()               // Storing the data as ints instead of strings.
    * NaiveBayes->Setup()                      // Calculates the table.
        * frequentSet->setCount()              // Makes all more complex calls to the table, where there are more then 1 condition.
    * IOfunctions->prittyPrintNaiveBayes()     // Output to file
        * database->predict()                  // Use the table to get the prediction.
        * id3->Node::test()
    
For more detail, please see the code itself.  
        
