# Activity-Tracker

## Project Description
An activity tracker was built using an  Arduino Nano 33 board. The following steps were followed to build this activity tracker.

### Data Collection: 

Data was collected using the IMU (LSM9DS1) on the Arduino board. The activities that were considered are 
Sitting, Standing, Walking, Ascending stairs, Descending stairs, Jumping and Dancing 


### Classification of the activities:

The collected data was used to train the model for classifying the activities. The following steps were taken to train the model:

-  Time-domain features were extracted from the collected data. The extracted features were used to train a 3 layered Neural Network with an accuracy of 93.4%. 
-  The raw data was also used to train another neural network.  
-  Two TensorFlow Lite models were generated for the above trained models


Finally, the model was deployed on the microcontroller.



