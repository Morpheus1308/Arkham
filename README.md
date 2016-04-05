# Arkham
##Introduction
This project is a show case for C++, QML and Qt.

The code mimics a surrogate system for managing residents at the Arkham Asylum - the inmates are not running this one, I can tell you. There are four kinds of residens in the Asylum:

 * Patients, who have come kind of mental disorder. POssibly gained by their unique insight.
 * Guards, whose primary task is to make sure the patients stay still when being drugged.
 * Medical Staff, who make sure patients get the medicine they need, or at leas an abundance of medicine.
 * Alchemists, who are directors or other kind of upper managers whose primary function is to make sure no scandals are leaked.
 
The code in this repository allows residents to log in and see details about theother residents based on certain rules:

 * Alchemists can read and write any kind of resident.
 * Medical Staff can read medical staff, guards and patients and write to patients.
 * Guards can read guards and patients
 * Patients cannot read or write anything. They are under care, right?
 
## Code Layout
Code is split in a model and two user interfaces. 

The model holds the actual resident data and are stored on our local machine in your 'home' folder. 

The two user interfaces are a widget based one and a qml based one.

The widget based one  allows you to create new residents and delete existing ones - if you are logged in with the needed priviledges (hint: "a@a.a" with password "SuperSecretRandomPassword" can do a lot!). Using the widget interface, you can also see the residents you are allowed to see.
Using the widgetbased you can also create new accounts and have your password reset. New accounts and password resets are supposed to be mailed to you, but are in this case just outputted to the debug out.

The QML based one, mimics a phone app residents can use to get a less detailed overview of the residente they may view.

#Using the user interfaces
You can log in as alchemist with "a@a.a" and "SuperSecretRandomPassword", as Medical Staff with "m@m.m" and "SuperSecretRandomPassword", as Guard with "g@g.g" and "SuperSecretRandomPassword" and as a patient with "p@p.p" and "SuperSecretRandomPassword" as password.

Have fun. 


#Note

  1 :  This code has been build with against Qt 5.5 on Linux with gcc and on Windows 7 against Qt 5.5 with msvc. You may experience trouble executing the qml ui. In that case, just disable it in the root .pro file.
  
  2: Upon launch, the program checks if $(HOME)/arkham.arf exists on your machine and if not it is created. This is the file that keeps records of residents. If you want to clear the database, remove this file.
