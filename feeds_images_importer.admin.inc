<?php

/**
 * @file
 * This is the file containing the settings form.
 */

/**
 * Settings form.
 *
 * @return array();
 *   Function to return the configuration page form.
 */
function feeds_images_importer_settings_form() {

  $form = array();

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t("Configorations for Feed Image Module:"),
  );

  $node_types = array();

  foreach (node_type_get_types() as $node) {
    $node_types[$node->type] = $node->name;
  }
  $form['settings']['on_off_box'] = array(
    '#type' => 'fieldset',
    '#title' => t("Feed Image state:"),
  );

  $form['settings']['content_types'] = array(
    '#type' => 'fieldset',
    '#title' => t("Choose content types:"),
    '#states' => array(
      'visible' => array(
        ':input[name="feeds_images_importer"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['settings']['on_off_box']['feeds_images_importer_state'] = array(
    '#type' => 'checkbox',
    '#title' => t('Turn on/off the module.'),
    '#description' => t('Turning the module off is going to disable it but it is not going to affect any of the already saved content.'),
    '#default_value' => variable_get('feeds_images_importer', ""),
  );

  $form['settings']['content_types']['feeds_images_importer_content_type'] = array(
    '#type' => 'checkboxes',
    '#options' => $node_types,
    '#title' => t('What content types do you want to use this module with?'),
    '#default_value' => variable_get('feeds_images_importer_content_type', array()),
    '#description' => t('All the content types that are chosen are going to have images attached to their image fields when they are generated with Feeds module. If the Image Field is set to multiple all the available images are to be dowlnoaded.'),
  );

  $form['settings']['choose_field'] = array(
    '#type' => 'fieldset',
    '#description' => t('List of all available fields attached to the chosen content types.'),
    '#title' => t("Choose Fields for images to be attached:"),
    '#states' => array(
      'visible' => array(
        ':input[name="feeds_images_importer"]' => array('checked' => TRUE),
      ),
    ),
  );

  // Get all the fields from the content type.
  $instances = field_info_instances('node');
  $fields = array();
  foreach ($instances as $types) {
    foreach ($types as $field) {
      $fields[$field['bundle']][$field['field_name']] = $field['label'] . " (" . $field['field_name'] . ")";
    }
  }

  if (!empty($types)) {
    foreach ($node_types as $machine_name => $name) {

      $form['settings']['choose_field'][$machine_name] = array(
        '#type' => 'fieldset',
        '#title' => $name . ":",
        '#states' => array(
          'visible' => array(
            ':input[name="feeds_images_importer_content_type[' . $machine_name . ']"]' => array('checked' => TRUE),
          ),
        ),
      );

      $form['settings']['choose_field'][$machine_name]['feeds_images_importer_' . $machine_name] = array(
        '#type' => 'radios',
        '#options' => $fields[$machine_name],
        '#default_value' => variable_get('feeds_images_importer_' . $machine_name, ""),
        '#required' => FALSE,
        '#description' => t("It is a MUST to choose a field of type 'image'."),
      );
    }
  }

  return system_settings_form($form);
}
