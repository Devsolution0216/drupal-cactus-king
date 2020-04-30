$Id
README.txt
==========
The WURFL module is an easy wrapper for the WURFL project (http://wurfl.sourceforge.net/). It can be used as an API for module developers, or themers in order to make adaptive websites. The module doesn't expose end-user functionality.

WHAT IS WURFL
=============
The WURFL is an XML configuration file which contains information about capabilities and features of many mobile devices.

The main scope of the file is to collect as much information as we can about all the existing mobile devices that access WAP pages so that developers will be able to build better applications and better services for the users.

The WURFL project is an open source project and is intended for developers working with the WAP and Wireless.

See http://wurfl.sourceforge.net/ for a more detailed explanation. 

API
===
The module exposes an API for developers to use device information within their applications.

The API can be used in two ways:
1) Object oriented and specific to WURFL 
calling  wurfl_get_requestingDevice(), returns the $requestingDevice object. 
This object can be queried for device capabilities:
  e.g.: $requestingDevice->getCapability("brand_name") // returns the brandname
  
2) Functional approach, generic (Recommended)
In order to allow for other frameworks to take over device capability detection the module allows a more generic approach. Getting a capability can be done by calling wurfl_devicecapability($capability).
  e.g.: wurfl_devicecapability("brand_name") // returns the brandname
  
The mobile_tools module will provide a means of using an interface method towards other frameworks 
e.g. mobile_tools_devicecapability("brand_name") will call wurfl_devicecapability("brand_name"). In case an other framework is selected, [other_framework]_devicecapability("brand_name") will be called.


INSTALLATION
============
See INSTALL.txt

RELATED MODULES
===============
This module integrates with the Mobile Tools module (http://drupal.org/project/mobile_tools)

AUTHOR/MAINTAINER
=================
Tom Deryckere
Tom DOT Deryckere at siruna DOT com 
http://www.mobiledrupal.com

The WURFL project is initiated and maintained by Lucca Passani (http://www.passani.it/). This Drupal WURFL module is mainly a wrapper to give easy access to Drupal Developers.


