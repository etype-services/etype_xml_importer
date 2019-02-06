<?php

/* admin settings form */
function etype_xml_importer_admin() {

  // Default Import URL
  $tmp = variable_get('etype_xml_base_import_url');
  $etype_xml_base_import_url = empty($tmp)? 'http://olivexml.etypeservices.com/olivexml/': $tmp;

  // Choose node type into which to import
  $node_types = node_type_get_types();
  $types = [];
  foreach ($node_types as $item) {
    $types[$item->type] = $item->name;
  }
  $tmp = variable_get('etype_xml_node_type');
  // default should be article normally
  $default_type = (empty($tmp))? 'article': $tmp;

  /* get available text formats and make into array */
  $filter_formats = filter_formats();
  $formats = [];
  foreach($filter_formats as $format) {
    $formats[$format->format] = $format->name;
  }

  /* get fields */
  $fields_info = field_info_instances('node', $default_type);
  $fields = [];
  foreach($fields_info as $field) {
    $fields[$field['field_name']] = $field['label'];
  }

  $form = [];

  /* importer settings */
  $form['etype_xml_importer'] = [
    '#type' => 'fieldset',
    '#title' => t('Basic configuration'),
  ];

  $form['etype_xml_importer']['etype_xml_import_file'] = [
    '#type' => 'textfield',
    '#title' => t('Filename'),
    '#description' => t('Enter the file name or names to import. Separate multiple files with a comma.'),
    '#size' => 55,
    '#default_value' => variable_get('etype_xml_import_file'),
  ];

  $form['etype_xml_importer']['etype_xml_cron_schedule'] = [
    '#type' => 'textfield',
    '#title' => t('Cron Schedule'),
    '#description' => t('Enter a valid cron schedule'),
    '#size' => 55,
    '#default_value' => variable_get('etype_xml_cron_schedule'),
  ];

  $form['etype_xml_importer']['etype_xml_subhead_field'] = [
    '#title' => t('Subhead field'),
    '#type' => 'select',
    '#description' => 'The Drupal field to use for the imported subhead.',
    '#options' => $fields,
    '#default_value' => variable_get('etype_xml_subhead_field', 'field_subhead'),
  ];

  $form['etype_xml_importer']['etype_xml_byline_field'] = [
    '#title' => t('Byline field'),
    '#type' => 'select',
    '#description' => 'The Drupal field to use for the imported byline.',
    '#options' => $fields,
    '#default_value' => variable_get('etype_xml_byline_field', 'field_dateline'),
  ];

  /* advanced importer settings */
  $form['etype_xml_importer_advanced'] = [
    '#type' => 'fieldset',
    '#title' => t('Advanced configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  $form['etype_xml_importer_advanced']['etype_xml_base_import_url'] = [
    '#type' => 'textfield',
    '#title' => t('Base Import Url'),
    '#description' => t('Url from which to import xml.'),
    '#size' => 55,
    '#default_value' => $etype_xml_base_import_url,
  ];

  $form['etype_xml_importer_advanced']['etype_xml_node_type'] = [
    '#title' => t('Content Type'),
    '#type' => 'select',
    '#description' => 'Choose the content type into which to import stories.',
    '#options' => $types,
    '#default_value' => $default_type,
  ];

  $form['etype_xml_importer_advanced']['etype_xml_subhead_format'] = [
    '#title' => t('Subhead format'),
    '#type' => 'select',
    '#description' => 'Select the "Subhead" field text format.',
    '#options' => $formats,
    '#default_value' => variable_get('etype_xml_subhead_format', 'plain_text'),
  ];

  $form['etype_xml_importer_advanced']['etype_xml_pulled_quote_format'] = [
    '#title' => t('Pull Quote format'),
    '#type' => 'select',
    '#description' => 'Select the "Pull Quote" field text format.',
    '#options' => $formats,
    '#default_value' => variable_get('etype_xml_pulled_quote_format', 'plain_text'),
  ];

  $form['etype_xml_importer_advanced']['etype_xml_import_classifieds'] = [
    '#title' => t('Check to import Olive classified section.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('etype_xml_import_classifieds', 0),
  ];

  $form['etype_xml_importer_advanced']['etype_xml_default_tags'] = [
    '#type' => 'textfield',
    '#title' => t('Default Tag Term Ids'),
    '#description' => t('Comma-separated, leave blank if none.'),
    '#size' => 55,
    '#default_value' => variable_get('etype_xml_default_tags', ''),
  ];

  return system_settings_form($form);
}