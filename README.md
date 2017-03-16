# Assignment 4: ID3 Algorithm Implementation

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

In the build folder you may find the executable **data_a4**.  
A symbolic link has been provided in the top level directory called  **ass4**.  
The program takes in **1**, **2**, or **3** arguments.

* A Data File
* A target header in said data file
* A file containing test values

Running this regularly requires putting this in the PATH variable, or can be run by giving the path.  In most cases the easiest form of this is to append `./` to the beinging of the path name.

```
./ass4 <Data File> [<Classifier Target> <Test File>]
```

To bring up this information, simply use the command:
```
./ass4 -h
```

The samples provided limit the user to 2 option variables, however, I have found nothing to indicate that ID3 must be limited to this search field.
I have used generic enough functions to allow for multiple values from being selected, and so I will not limit the user.  
If there is something I am unaware with in ID3 that prevents multiple value targets from being selected, then by all means, don't select those values.
In the interactive mode, I will indicate which values are binary.

## Design

### File structure
There are two folders of files, include and src.  Like many C and C++ project, an individual .h file is provided for every .cpp file, excluding main.

The .h files will hopefuly serve as a guide to the .cpp files.

I will highlight some functions that may not have as clear uses.

Some files were not removed from the last assignment.  They are included because removing them was not found to be needed.

#### main
Provides the main function to run the program, checks for input value ranges.

#### IOfunctions
Provides the input and output functions.

* readCSV: the input function that returns a database object.  Optionaly a test set can also be read in.
* prittyPrintID3: the output function that outputs the tree along with supporting data, and test results.

#### database
Stores values read in from a dataset.  Can check the data set for frequencies that comply with a frequent set,
create the initial frequent sets from the dataset.

* encode takes in a string and a column number.  This is used to encode that string as an integer, for faster use.
* decode takes a pair of integers, and gives back the original string.
* createDataset seeing as many tables need to be used, the createDataset function pulls out a table from the database for ues when recombining.
* createTestDataset is for the test set, but is essentialy the same.


#### frequentSet
Not used here.

#### rule
Not used here.

#### apriori
Not used here.

###id3
Creates the tree.

* Class Node represents a tree created by id3
* createTree is the setup class that will begin the process and return the full tree.
* entropy calculates the entropy of a given list.
* potentialGain calculates the data gain of splitting along a value.  
* Node::bestGain will run potential gain on every option, and pick the best one to use.
* Node::test tests a given entry on the tree.
* Node::Node(dataSet& set, int tieBreak) is recursive and will make the entire tree.
* Node(int val) always creates a leaf and exists only to create leaf nodes.

### Function 
Now, there are quite a few function calls in this program, so I will provide a simplified view to the important highlights.

* main()
    * IOfunctions->readCSV()                   // Reading in data.
        * database->addData()                  // Read in each line
            * database->encode()               // Storing the data as ints instead of strings.
    * id3->createTree()                        // Starts creating the tree.
        * id3->Node::Node()                    // Each node is created, and will go though the steps of splitting the list and making children.
            * id3->entropy()                   // Calculating the entropy of the node, end here if it is 0
            * id3->Node::bestGain()            // Figure out how to split.
                * id3->potentialGain()         // Check each option for how good it is.
                    * id3->entropy()           // used in calculating potential gain.
            * id3->Node::Node()                // Recurse on children.
    * IOfunctions->prittyPrintID3()            // Output to file
        * database->decode()                   // Use the decode function to get back the strings from the ints.
        * id3->Node::test()
    
For more detail, please see the code itself.  
        