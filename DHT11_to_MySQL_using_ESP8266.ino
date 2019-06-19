// HT11 to MySQL using ESP8266

// Version 1.01

// Compiled by Colin Cunningham of Q Metrics Ltd

// https://github.com/Q-Metrics/DHT11-to-MySQL-using-ESP8266

// This scritp is free to use, modify, and distribute under GNU General Public License v3.0

// Please reference Q Metrics Ltd if used in your live projects


// SET UP INSTRUCTIONS

//  1.  Create a table in your web hosted MySQL Database with the following columns
//    ID (Auto Increment)
//    sensor (var)
//    location (var)
//    value 1 (float)
//    value 2 (float)
//    value 3 (float)

//  2.  Enter your database name and chosen table name into the appropriate variables below.

//  3.  Enter your database access username and password into the appropraite variables below.

//  4.  Using cPanel or your web hosting administration system, provide permission for your local ip address to access your web hosted MySQL Database.

//  5.  Enter your MySQL server IP address into the appropriate variable below.

//  6.  Enter your local wifi network credentials into the appropriate variables below.

//  7.  Enter a name for your sensor into the appropiate variable below.

//  8.  Enter a name for your sensor's location into the appropriate variable below.

//  9.  Upload the script to your ESP8266.

//  10. Access the uploaded data via MySQLAdmin or your chosen MySQL Client.



//Install Required Wifi Libraries
    #ifdef ESP32
      #include <WiFi.h>
      #include <HTTPClient.h>
    #else
      #include <ESP8266WiFi.h>
      #include <ESP8266HTTPClient.h>
      #include <WiFiClient.h>
    #endif

//Install DHT11 Sensor Libraries
    #include <DHT.h>
    #include <Adafruit_Sensor.h>

//Install MySQL Libraries
    #include <MySQL_Connection.h>
    #include <MySQL_Cursor.h>

// Define MySQL Server IP Address
    IPAddress server_addr(91,207,51,56);  

// Define MySQL Database Access Credentials
    char dbuser[] = "XXXXXX";              
    char dbpassword[] = "XXXXXX";       

// Define MySQL Database and Table Names
    char dbname[] = "XXXXXX";
    char dbtable[] = "XXXXXX";

// Define Local Network Access Credentials
    const char* ssid     = "XXXXXX";
    const char* password = "XXXXXX";

// Define Sensor Pins
    #define DHT11_PIN 2
    DHT DHT(DHT11_PIN,DHT11);

// Create Wifi Client Instance
    WiFiClient client; 

// Create MySQL Connection Instance
    MySQL_Connection conn((Client *)&client);





void setup() {

// Opern Serial Connection
    Serial.begin(115200);
    //Serial.setDebugOutput(true);

// Start DHT11 Sensor 
DHT.begin();
  
// Establish Wifi Connection With Local Network Which Must Be Connected to the Internet and Report Progress through Serial
    WiFi.begin(ssid, password);
      Serial.println("Connecting");
      while(WiFi.status() != WL_CONNECTED) { 
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.print("Connected to WiFi network with IP Address: ");
      Serial.println(WiFi.localIP());


// If Your MySQL Connection Fails in the Loop, Uncomment the Following Delay Command to delay MySQL Connection Attempt for 5 Seconds After Wifi Connection.
    //delay(5000); 

}






void loop() {

//Check WiFi Connection Status
    if(WiFi.status()== WL_CONNECTED){


//Connect to MySQL Server 
    Serial.print("Connecting to database at: ");
    Serial.println(server_addr);
  
// Check MySQL Servcer Connection and Continue
    if (conn.connect(server_addr, 3306, dbuser, dbpassword)) {



// Set or Retrieve Values to Be Passed to Database
    char sensorName[] = "DHT11";
    char sensorLocation[] = "Livingroom";
    float value1 = DHT.readTemperature();
    float value2 = DHT.convertCtoF(value1);
    float value3 = DHT.readHumidity();

// Show Data to Be Stored in Serial
    Serial.print("Sensor Name = ");
    Serial.print(sensorName);
    Serial.print(", Sensor Location = ");
    Serial.print(sensorLocation);
    Serial.print(", Value 1 = ");
    Serial.print(value1);
    Serial.print(", Value 2 = ");
    Serial.print(value2);
    Serial.print(", Value 3 = ");
    Serial.print(value3);
    Serial.println("");


// Define MySQL Query to Insert Data into Database Table
    char query[255];
    sprintf(query, "INSERT INTO %s.%s (sensor, location, value1, value2, value3) VALUES ('%s','%s',%f,%f,%f)", dbname, dbtable, sensorName, sensorLocation, value1, value2, value3);


// Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);


// Uncomment the Following 3 Lines Send MySQL Query to Serial if Having Syntax Errors
//Serial.println("");
//Serial.println(query);
//Serial.println("");


// Execute the query
    cur_mem->execute(query);
// Note: since there are no results, we do not need to read any data

// Deleting the cursor also frees up memory used
    delete cur_mem;

// Confirm Data Recorded to Serial
    Serial.println("Data recorded.");

    }
    else{
      
// Send Connection Failure Info to Serial if MySQL Connection Fails
    Serial.println("Connection failed.");
    }

// Close Database Conection
    conn.close();

    }
    else {
// Send Wifi Disconnection Info to Serial if Wifi Has Disconnected
    Serial.println("WiFi Disconnected");
    }
  

//Update Database Every 5 Minutes (Minus 4 Seconds To Account For Time Requird To Connect To MySQL Database
    delay(296000);  

    }
