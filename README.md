# DHT11 to MySQL using ESP8266
Store DHT11 Data to MYSQL Using ESP8266 and Existing Libraries

After hunting many other souces I could not find a single Arduino IDE to accomplish this, but what I did find is that it could be done using existing libraries.

Using libraries already available in the Arduino IDE this single Arduino Code will enable you to connect to an existing MySQL database and store temperature and hunidity readins from a DHT11.

This could easily be modified to store other sensor outputs.



This scritp is free to use, modify, and distribute under GNU General Public License v3.0

Please reference Q Metrics Ltd if used in your live projects


SET UP INSTRUCTIONS

1.  Create a table in your web hosted MySQL Database with the following columns
    ID (Auto Increment), sensor (var), location (var), value 1 (float), value 2 (float), value 3 (float), reading_time (TIMESTAMP)

  2.  Enter your database name and chosen table name into the appropriate variables within the script

  3.  Enter your database access username and password into the appropraite variables within the script.

  4.  Using cPanel or your web hosting administration system, provide permission for your local ip address to access your web hosted MySQL Database.

  5.  Enter your MySQL server IP address into the appropriate variable within the script.

  6.  Enter your local wifi network credentials into the appropriate variables within the script.

  7.  Enter a name for your sensor into the appropiate variable within the script.

  8.  Enter a name for your sensor's location into the appropriate variable within the script.

  9.  Upload the script to your ESP8266.

  10. Access the uploaded data via MySQLAdmin or your chosen MySQL Client.
