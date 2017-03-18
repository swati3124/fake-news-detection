<------------------------- FAKE NEWS RECOGNITION ----------------------->

MEMBER DETAILS :-

Heenal Doshi      004758927     doshi.heenal@gmail.com
Omkar Patil     904760474     omkar.9194@gmail.com
Pranav Sodhani      804591764     sodhanipranav@gmail.com
Shubham Mittal      104774903     mitshubh@gmail.com
Swati Arora     404758379     swati3124@gmail.com


THE PROJECT STRUCTURE CONSISTS OF TWO MAIN FOLDERS ;- CODE, DATA.

######THE CODE FOLDER HAS ALL THE NECESSARY SCRIPTS, CODE REQURIED TO PROCESS, TRAIN AND PREDICT THE NEWS ARTICLES DATA STORED IN THE 'DATA' FOLDER
 
######THE DATA FOLDER CONSISTS OF TWO DAT FILES.:-

THE FIRST DAT FILE, TRAININGSET CONSISTS OF 500 REAL, 500 FAKE NEWS ARTICLES.
THE SECOND DAT FILE TRAININGSETLABELS CONSISTS OF THE LABELS FOR THE ABOVE ARTICLES AS FAKE/REAL.


<--------------------------------------------- EXECUTION STEPS :- ---------------------------------->
1) RUN THE PARSEDATASET.JAVA FILE TO CONVERT THE TRAININGSET.DAT, TRAININGSETLABELS.DAT TO FAKE AND REAL FOLDER. 
THESE FOLDERS WILL CONTAI 500 FAKE AND REAL .TXT FILES RESPECTIVELY

<---------------------------------------------SEMANTIC ANALYSIS :- ---------------------------------->


2)INSTALL MALLET (http://mallet.cs.umass.edu/)

3)AFTER THIS WE WOULD BE USING A TOOL CALLED MALLET FOR CONVERTING THE PROCESSED FILES IN FAKE, REAL FOLDER TO GET 
FAKE_KEYS.TXT,FAKE_COMPOSITION.TXT AND REAL_KEYS.TXT, REAL_COMPOSITION.TXT FILES RESPECTIEVLY.

TO USE THE MALLET TOOL FOR DOING THE ABOVE, INSTALL MALLET AND EXECUTE THE FOLLOWING COMMANDS. PLEASE TAKE CARE OF
THE PATH WHILE EXECUTING THE COMMANDS


./bin/mallet import-dir --input /Users/swati.arora/Desktop/FakeNews/Real/ --output real.mallet --keep-sequence --remove-stopwords

./bin/mallet import-dir --input /Users/swati.arora/Desktop/FakeNews/Fake/ --output fake.mallet --keep-sequence --remove-stopwords

./bin/mallet train-topics --input fake.mallet --num-topics 20 --output-state fake-state.gz --output-topic-keys fake_keys.csv --output-doc-topics fake_composition.csv

./bin/mallet train-topics --input real.mallet --num-topics 20 --output-state real-state.gz --output-topic-keys real_keys.csv --output-doc-topics real_composition.csv


4)After this execute, the feature_generation.py, this will produce the output_fake.csv , output_real.csv which will contain the topic_proximity
for every file.

<---------------------------------------------SYNTACTIC ANALYSIS :- ---------------------------------->


5)INSTALL BLLIPPARSER FOR PYTHON 2.7
6)RUN GET_LOG_SCORE.PY 
7)THIS WILL GENERATE OUTPUT_PGRAMS_FAKE.CSV , OUTPUT_PGRAMS_REAL.CSV. THIS WILL CONTAIN THE PGRAM VALUE FOR EVERY SENTENCE  
IN A FILE, FOR EVERY FAKE/REAL FILE RESPECTIVELY.


8)After this execute, the svm.py file . In this we will be reading the topic_word_density from the fake_composition,real_composition file. We will also
be reading the topic_proximity from the earlier generated output_fake, output_real.csv files. Thus we will be having 2 such features for every topic (20 topics).
Thus we will be having 40 features, which will be fed to the svm along with the lable of the file (fake/real). At. the same time the pgrams feature calculated
earlier during syntactic analysis will also be fed to the svm. SVM will thus be trained.

9)after this we pass testing inputs to the svm to get the confusion matrix and results etc




