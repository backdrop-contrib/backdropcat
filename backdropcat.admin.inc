<?php

/**
 * @file
 * Admin form to manage module settings
 *
 */

/**
 * Define the form for manage backdropcat settings
 *
 */
function backdropcat_form($form, &$form_state) {
  $config = config('backdropcat.settings');

  $form['powered_by_block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Powered by block'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['powered_by_block']['url_update'] = array(
    '#type' => 'checkbox',
    '#title' => t('Update url'),
    '#default_value' => $config->get('url_update'),
    '#description' => t('Whether to change the url of the Backdropcms\' link is pointing to.'),
  );
  $form['powered_by_block']['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => $config->get('url'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => FALSE,
    '#states' => array(
      'invisible' => array(
        ':input[name="url_update"]' => array('checked' => FALSE),
      ),
    ),
    '#description' => t('Set the url of the link of backdropcms site is pointing to'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}


//TODO: add a hook_validate function.

/**
 * Implements hook_submit().
 */
function backdropcat_form_submit($form, &$form_state) {
  $config = config('backdropcat.settings');
  $url = trim($form_state['values']['url']);
  $url_update = (int) $form_state['values']['url_update'];
  $config->set('url',     $url);
  $config->set('url_update',      strtolower($url_update));
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
