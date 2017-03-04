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

## Design

### File structure
There are two folders of files, include and src.  Like many C and C++ project, an individual .h file is provided for every .cpp file, excluding main.

The .h files will hopefuly serve as a guide to the .cpp files.

I will highlight some functions that may not have as clear uses.

#### main
Provides the main function to run the program, checks for input value ranges.

#### IOfunctions
Provides the input and output functions.

* readCSV: the input function that returns a database object.
* prittyPrint: the output function that outputs all of the rules along with supporting data.

#### database
Stores values read in from a dataset.  Can check the data set for frequencies that comply with a frequent set,
create the initial frequent sets from the dataset.

* encode takes in a string and a column number.  This is used to encode that string as an integer, for faster use.
* decode takes a pair of integers, and gives back the original string.
* setCount takes in a frequentSet, and preforms all the steps needed to check in the database the frequent count. 
    * If setCount is asked to check the same frequentSet, then it will have stored the value so it would not have to do the check again.
    * using this function initialises the frequentSet class.


#### frequentSet
A class representing a set that also contains a frequency.  Frequencies may be -1 to be null, and will be 0 when not initialised. 

* getFilter as apposed to getRawFilters will construct an array for easy use with the database for filtering.
* getRawFilters will just return the raw list used inside the class.
* combine is a join that will only work if the two sets can be joined.  
    * Selection is done such that only 2 parents can make a set.  No other set of the possible parents will work.
    * This is done by ensuring the first n-1 elements are the same, and that the last elements differ.
    * The non null result is not initialised.
* remaining will return a frequent set based on the given set, such that only the differing elements are in the new set.
    * This is most useful with rule creation as the set ABC, may have a tail B and will need to calculate the head set AC.
    * The result will always be not initialised.

#### rule
A class representing a rule.

* combine is once again a join for rules, it will simply try and join the tails of the two lists.  
    * If this works, a initialised rule will be returned.

####apriori
Provides the main algorithmic glue for the rule generation.

### Function 
Now, there are quite a few function calls in this program, so I will provide a simplified view to the important highlights.

* main()
    * IOfunctions->readCSV()                   // Reading in data.
        * database->addData()                  // Read in each line
            * database->encode()               // Storing the data as ints instead of strings.
    * apriori->apriori()                       
        * apriori->getFrequentSets()           // Create all frequent sets.
            * database->getFirstFrequentSets() // Get all 1 item frequent sets.
                * database->setCount()         // Store those frequency values for later.
            * frequentSet->combine()           // make n+1 item sets
            * database->setCount()             // Calculate and store all the frequency values.
        * apriori->getRules()                  // Create all the confident rules from the frequent sets.
            * rule->getFirstRules()            // Get all 1 result rules.
                * database->setCount()         // Check frequencies as needed to figure confidence out.
            * rule->combine()                  // Get all n+1 rules.
                * database->setCount()         // Check frequencies as needed to figure confidence out.
    * IOfunctions->prittyPrint()               // Output to file
        * database->decode()                   // Use the decode funtion to get back the strings from the ints.
    
For more detail, please see the code itself.  
        