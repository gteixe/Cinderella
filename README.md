# Cinderella


#Access the remote server
  
  $ssh username@t3btch008.mit.edu
  
#From the remote server, run snapshotCinderellaDb.py
  
  $python snapshotCinderellaDb.py

#Once you have ascertained that the .py file is dumping the data from the database, copy the db dump into a .txt file
  
  $python snapshotCinderellaDb.py >> snapshotCinderellaDb.txt
  
#In a new terminal, from your local computer perform a secure copy of the .txt file
  
  $scp username@t3btch008.mit.edu:snapshotCinderella.txt ~/
  
#Now you can create the graphs of the data by running Cinderella.C. This will automatically save the .png files of the all the graphs.

  $root -l .x Cinderella.C
