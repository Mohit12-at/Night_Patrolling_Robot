{\rtf1\ansi\ansicpg1252\cocoartf2638
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 \
#include <Arduino.h>\
#if defined(ESP32)\
  #include <WiFi.h>\
#elif defined(ESP8266)\
  #include <ESP8266WiFi.h>\
#endif\
#include <ESP_Mail_Client.h>\
\
#define WIFI_SSID "	MG\'94\
#define WIFI_PASSWORD "12345678"\
\
#define SMTP_HOST "smtp.gmail.com"\
#define SMTP_PORT 465\
\
/* The sign in credentials */\
#define AUTHOR_EMAIL "patrollingrobot.iiita@gmail.com"\
#define AUTHOR_PASSWORD "iglfhbilbcaxnxri"\
\
/* Recipient's email*/\
#define RECIPIENT_EMAIL "iec2019009@iiita.ac.in"\
\
/* The SMTP Session object used for Email sending */\
SMTPSession smtp;\
\
/* Callback function to get the Email sending status */\
void smtpCallback(SMTP_Status status);\
int inPin = 5;\
int val=LOW;\
void setup()\{\
\
  pinMode(inPin, INPUT);\
  Serial.begin(115200);\
  Serial.println();\
  Serial.print("Connecting to AP");\
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);\
  while (WiFi.status() != WL_CONNECTED)\{\
    Serial.print(".");\
    delay(200);\
  \}\
  Serial.println("");\
  Serial.println("WiFi connected.");\
  Serial.println("IP address: ");\
  Serial.println(WiFi.localIP());\
  Serial.println();\
  smtp.debug(1);\
\
  /* Set the callback function to get the sending results */\
  smtp.callback(smtpCallback);\
\
  /* Declare the session config data */\
  ESP_Mail_Session session;\
\
  /* Set the session config */\
  session.server.host_name = SMTP_HOST;\
  session.server.port = SMTP_PORT;\
  session.login.email = AUTHOR_EMAIL;\
  session.login.password = AUTHOR_PASSWORD;\
  session.login.user_domain = "";\
\
  /* Declare the message class */\
  SMTP_Message message;\
\
  /* Set the message headers */\
  message.sender.name = "ESP";\
  message.sender.email = AUTHOR_EMAIL;\
  message.subject = "ALert";\
  message.addRecipient("Mayank", RECIPIENT_EMAIL);\
\
  /*Send HTML message*/\
  String htmlMsg = "<div style=\\"color:#2f4468;\\"><h1>There is intruder in your home!</h1><p>Sent from Patrolling Robot </p></div>";\
  message.html.content = htmlMsg.c_str();\
  message.html.content = htmlMsg.c_str();\
  message.text.charSet = "us-ascii";\
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;\
\
  /*\
  //Send raw text message\
  String textMsg = "Hello World! - Sent from ESP board";\
  message.text.content = textMsg.c_str();\
  message.text.charSet = "us-ascii";\
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;\
  \
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;\
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/\
\
  /* Set the custom message header */\
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");\
\
  /* Connect to server with the session config */\
  if (!smtp.connect(&session))\
    return;\
\
  /* Start sending Email and close the session */\
  if (!MailClient.sendMail(&smtp, &message))\
    Serial.println("Error sending Email, " + smtp.errorReason());\
\}\
\
void loop()\{\
  val = digitalRead(inPin);\
\
  if( val == HIGH)\
  \{\
    val = LOW;\
    /** Enable the debug via Serial port\
   * none debug or 0\
   * basic debug or 1\
  */\
  smtp.debug(1);\
\
  /* Set the callback function to get the sending results */\
  smtp.callback(smtpCallback);\
\
  /* Declare the session config data */\
  ESP_Mail_Session session;\
\
  /* Set the session config */\
  session.server.host_name = SMTP_HOST;\
  session.server.port = SMTP_PORT;\
  session.login.email = AUTHOR_EMAIL;\
  session.login.password = AUTHOR_PASSWORD;\
  session.login.user_domain = "";\
\
  /* Declare the message class */\
  SMTP_Message message;\
\
  /* Set the message headers */\
  message.sender.name = "CC3";\
  message.sender.email = AUTHOR_EMAIL;\
  message.subject = "Alert";\
  message.addRecipient("Mayank", RECIPIENT_EMAIL);\
\
  String htmlMsg = "<div style=\\"color:#2f4468;\\"><h1>There is intruder in your home!</h1><p>Sent from Patrolling Robot</p></div>";\
  message.html.content = htmlMsg.c_str();\
  message.html.content = htmlMsg.c_str();\
  message.text.charSet = "us-ascii";\
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;\
\
  /*\
  //Send raw text message\
  String textMsg = "Hello World! - Sent from ESP board";\
  message.text.content = textMsg.c_str();\
  message.text.charSet = "us-ascii";\
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;\
  \
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;\
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/\
\
  /* Set the custom message header */\
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");\
\
  /* Connect to server with the session config */\
  if (!smtp.connect(&session))\
    return;\
\
  /* Start sending Email and close the session */\
  if (!MailClient.sendMail(&smtp, &message))\
    Serial.println("Error sending Email, " + smtp.errorReason());\
  \}\
\}\
\
/* Callback function to get the Email sending status */\
void smtpCallback(SMTP_Status status)\{\
  /* Print the current status */\
  Serial.println(status.info());\
\
  /* Print the sending result */\
  if (status.success())\{\
    Serial.println("----------------");\
    ESP_MAIL_PRINTF("Message sent success: %d\\n", status.completedCount());\
    ESP_MAIL_PRINTF("Message sent failled: %d\\n", status.failedCount());\
    Serial.println("----------------\\n");\
    struct tm dt;\
\
    for (size_t i = 0; i < smtp.sendingResult.size(); i++)\{\
      /* Get the result item */\
      SMTP_Result result = smtp.sendingResult.getItem(i);\
      time_t ts = (time_t)result.timestamp;\
      localtime_r(&ts, &dt);\
\
      ESP_MAIL_PRINTF("Message No: %d\\n", i + 1);\
      ESP_MAIL_PRINTF("Status: %s\\n", result.completed ? "success" : "failed");\
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);\
      ESP_MAIL_PRINTF("Recipient: %s\\n", result.recipients);\
      ESP_MAIL_PRINTF("Subject: %s\\n", result.subject);\
    \}\
    Serial.println("----------------\\n");\
  \}\
\}}