<?php
// $Id:

/**
 * @file
 *   Configuration file for the WURFL module
 */
 
/**
 * Settings page 
 *
 */
function wurfl_settings() {
  $output = '';
  // Check if the library is installed.
  $library = wurfl_check_library();
  if($library === FALSE) {
    $output .= theme('wurfl_status', t('The WURFL PHP library cannot be found. Read the INSTALL.txt file for instructions.'), 'error');   
    return $output;
  }
  else {
    $output .= theme("wurfl_status", t('The WURFL library is successfully installed in ' . $library));
  }
  
  // Check if a resources directory is created
  if(!file_exists("$library/resources") || !file_exists("$library/cache")) {
    $output .= theme("wurfl_status", t("Please create the 'resources' and 'cache' folder in !library. Copy wurfl.xml and wurfl-config.xml in this folder.", array('!library' => $library)), 'error');
    return $output;
  }
  else {
    // check if the wurfl xml file exist
    $xml =  "$library/resources/wurfl.xml";
    if(!file_exists($xml)) {
      $output .= theme("wurfl_status", t('The WURFL device file (wurfl.xml) is not found in !library/resources. Read the INSTALL.txt file for instructions.',  array('!library' => $library)), 'error');   
      return $output;
    }
    else {
      $output .= theme("wurfl_status", t('The WURFL device file (wurfl.xml) is found in !library/resources/wurfl.xml',  array('!library' => $library)));
      // Check if the wurfl-config file exist
      $config = "$library/resources/wurfl-config.xml";
      if(!file_exists($config)) {
        $output .= theme("wurfl_status", t('The WURFL configuration file (wurfl-config.xml) cannot be found in $library/resources. Read the INSTALL.txt file for instructions.'), 'error');  
        return $output; 
      }
      else {
        $output .= theme("wurfl_status", t('The WURFL library is successfully installed in $library/resources/wurfl-config.xml'));
        wurfl_boot();
        global $wurflManager;
        $info = $wurflManager->getWURFLInfo();
        $output .= '<h2>WURFL Version information</h2>';
        $output .= '<dl>';
        $output .= "<dt>Version: </dt> <dd>" . $info->__get('version') . "</dd>";  
        $output .= "<dt>Last Updated: </dt> <dd> " . $info->__get('lastUpdated') . "</dd>";   
        $output .= "<dt>Official URL: </dt> <dd> " . $info->__get('officialURL') . "</dd>";  
      } 
    }
  }
  return $output;
}


/**
 * Theme the status messages
 */
function theme_wurfl_status($message, $type = "status") {
  $output = "<div class=\"message $type\">\n";
  $output .= "<ul>\n";
  $output .= "<li>$message</li>\n";
  $output .= "</ul>\n";
  $output .= "</div>";

  return $output;
}