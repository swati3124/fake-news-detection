# -*- coding: utf-8 -*-
"""
Created on Fri Mar 10 12:10:05 2017

@author: swati.arora
"""

#from sklearn.utils import shuffle
#list_1, list_2 = shuffle(list_1, list_2)

from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix
import pandas as pd
import numpy as np
from sklearn import cross_validation  

fake_feature1 = pd.read_csv("fake_composition.csv", sep='\t', header=None)
real_feature1 = pd.read_csv("real_composition.csv",  sep='\t', header=None)

fake_feature2 = pd.read_csv("output_fake.csv", sep='\t', header=None)
real_feature2 = pd.read_csv("output_real.csv",  sep='\t', header=None)

fake_x1 = fake_feature1.iloc[:,2:]
fake_y = pd.DataFrame(np.zeros((500,1)))
real_x1 = real_feature1.iloc[:,2:]
real_y = pd.DataFrame(np.ones((500,1)))

fake_x2 = fake_feature2.iloc[:,2:]
real_x2 = real_feature2.iloc[:,2:]

df_fake = [fake_x1, fake_x2]
fake_x = pd.concat(df_fake, axis = 1)

df_real = [real_x1, real_x2]
real_x = pd.concat(df_real, axis = 1)


feature_matrix = fake_x.append(real_x, ignore_index=True)
label_matrix = fake_y.append(real_y, ignore_index=True)
X_train,X_test, Y_train, Y_test =  cross_validation.train_test_split(feature_matrix, label_matrix, test_size=0.1, random_state=42)


#SVM classification
svc_classifier = SVC(kernel = 'linear', probability=True)
fit_model = svc_classifier.fit(X_train, Y_train)
Y_predicted = fit_model.predict(X_test)

print "Confusion matrix \n"
print confusion_matrix(Y_test, Y_predicted) 