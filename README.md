# Assignment 3: Association Rule Mining Algorithm Implementation

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

In the build folder you may find the executable **data_a3**.  
A symbolic link has been provided in the top level directory called  **ass3**.  
The program takes in **3** arguments.

* A Data File
* A Minimum Support Rate
* A Minimum Confidence Rate

Running this regularly requires putting this in the PATH variable, or can be run by giving the path.  In most cases the easiest form of this is to append `./` to the beinging of the path name.

```
./ass3 <Data File> <Minimum Support Rate> <Minimum Confidence Rate>
```

To bring up this information, simply use the command:
```
./ass3 -h
```

## design

### File structure
There are two folders of files, include and src.  Like many C and C++ project, an individual .h file is provided for every .cpp file, excluding main.

The .h files will hopefuly serve as a guide to the .cpp files.

#### main
Provides the main function to run the program, checks for input value ranges.

#### IOfunctions
Provides the input and output functions.

#### database
Stores values read in from a dataset.  Can check the data set for frequencies that comply with a frequent set,
create the initial frequent sets from the dataset.

#### frequentSet
A class representing a set that also contains a frequency.

#### rule
A class representing a rule.

####apriori
Provides the main algorithmic glue for the rule generation.

### Function 
Now, there are quite a few function calls in this program, so I will provide a simplified view to the important highlights.

* main()
    * IOfunctions->readCSV()
        * database->addData()
            * database->encode()
    * apriori->apriori()
        * apriori->getFrequentSets()
            * database->getFirstFrequentSets()
            * frequentSet->combine()
            * database->setCount()
        * apriori->getRules()
            * rule->getFirstRules()
            * rule->combine()
    * IOfunctions->prittyPrint()
    
For more detail, please see the code itself.  
        