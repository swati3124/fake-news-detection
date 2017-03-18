###########################################################
 # Fake News Identification using Knowledge-Base (KBase) #
###########################################################

To Reproduce Results run the following commands --
	1. Open a terminal (Ctrl + Alt + T)
	2. cd KBase
	3. bin/knowledgeGraph data/dbpedia.edgelist data/dbpedia.nodes data/dbpedia.edgetypes
	4. Open another terminal (Ctrl + Alt + T)
	5. cd KBase
	6. cd TestScripts
	6. Rscript --verbose capital_state.R

Folders in KBase --
	1. src - contains the source code files
	2. bin - contains executibles
		a. parseInput.exe - parses the input dbpedia data (mapped-properties-cleaned) in turtle format and writes the corresponding graph
		b. knowledgeParser.exe - loads the graph files generated above to build a gigantic knowledge graph and provides an API to perform tasks on the graph
	2. data - contains the graph generated from trimmed down version of Dbpedia.
		a. dbpedia.edgelist
		b. dbpedia.edgetypes
		c. dbpedia.nodes
	3. Dbpedia - contains zipped versions of dbpedia dataset
	4. true_data - contains csv file having 50 correct instances of capitals and their states
	5. results - the final result folder

###########################################################
 # Build Project #
###########################################################


Build Prerequisites -- 
	1. gcc/g++ 
	2. Boost C++ Libraries (1.58 +)
	3. librdf++ from datagraph (https://github.com/datagraph/librdf)
	4. Install r-base for running R scripts (for ubuntu)

To Build the executables -- 
	1. cd KBase
	2. cmake - build .
	3. make parseInput
	4. make knowledgeGraph