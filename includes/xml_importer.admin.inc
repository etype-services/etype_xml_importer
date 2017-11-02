<?php

/* admin settings form */
function etype_xml_importer_admin() {

  $form = array();

  $tmp = variable_get('etype_xml_base_import_url');
  $etype_xml_base_import_url = !empty($tmp)? $tmp: 'http://olivexml.etypeservices.com/olivexml/';

  $node_types = node_type_get_types();

  var_dump($node_types);

  /* e_edition settings */
  $form['etype_xml_importer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Olive XML import configuration'),
  );

  $form['etype_xml_importer']['etype_xml_import_file'] = array(
    '#type' => 'textfield',
    '#title' => t('Filename'),
    '#description' => t('Enter the file name or names to import. Separate multiple files with a comma.'),
    '#size' => 55,
    '#default_value' => variable_get('etype_xml_import_file'),
  );

  $form['etype_xml_importer']['etype_xml_cron_schedule'] = array(
    '#type' => 'textfield',
    '#title' => t('Cron Schedule'),
    '#description' => t('Enter a valid cron schedule'),
    '#size' => 55,
    '#default_value' => variable_get('etype_xml_cron_schedule'),
  );

  $form['etype_xml_importer']['etype_xml_base_import_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base Import Url'),
    '#description' => t('Base Url from which to import xml.'),
    '#size' => 55,
    '#default_value' => $etype_xml_base_import_url,
  );

  return system_settings_form($form);
}