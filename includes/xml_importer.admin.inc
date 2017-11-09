<?php

/* admin settings form */
function etype_xml_importer_admin() {

  $form = array();

  // Default Import URL
  $tmp = variable_get('etype_xml_base_import_url');
  $etype_xml_base_import_url = empty($tmp)? 'http://olivexml.etypeservices.com/olivexml/': $tmp;

  // Choose node type into which to import
  $node_types = node_type_get_types();
  $types = array();
  foreach ($node_types as $item) {
    $types[$item->type] = $item->name;
  }
  $tmp = variable_get('etype_xml_node_type');
  // default should be article normally
  $default_type = (empty($tmp))? 'article': $tmp;

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
    '#description' => t('Url from which to import xml.'),
    '#size' => 55,
    '#default_value' => $etype_xml_base_import_url,
  );

  $form['etype_xml_importer']['etype_xml_node_type'] = array(
    '#title' => t('Content Type'),
    '#type' => 'select',
    '#description' => 'Choose the content type into which to import stories.',
    '#options' => $types,
    '#default_value' => $default_type,
  );

  $filter_formats = filter_formats();
  $formats = [];
  foreach($filter_formats as $format) {
    $formats[$format->format] = $format->name;
  }

  $form['etype_xml_importer']['etype_xml_kicker_format'] = array(
    '#title' => t('Kicker format'),
    '#type' => 'select',
    '#description' => 'Select a "kicker" field format.',
    '#options' => $formats,
    '#default_value' => variable_get('etype_xml_kicker_format', 'plain_text'),
  );

  return system_settings_form($form);
}