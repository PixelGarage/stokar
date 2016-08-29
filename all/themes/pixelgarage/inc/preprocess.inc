<?php
/**
 * Created by PhpStorm.
 * User: ralph
 * Date: 06.02.15
 * Time: 17:23
 */

/**
 * Preprocess variables for the html template.
 */
function pixelgarage_preprocess_html(&$vars) {
  // make sure jQuery UI and effects is loaded for anonymous users
  drupal_add_library('system', 'ui');
  drupal_add_library('system', 'effects');

  $vars['html_attributes_array']['lang'] = 'de';
}

/**
 * Override or insert variables for the page templates.
 */
function pixelgarage_preprocess_page(&$vars) {
  // hide titles on login forms
  pg_login_preprocess_page($vars);


}

/**
 * Remove the javascript file for views bootstrap carousel (implemented in pxlBehaviors)
 * @param $javascript
 */
function pixelgarage_js_alter(&$javascript) {
  $path = drupal_get_path('module', 'views_bootstrap') . '/js/views-bootstrap-carousel.js';
  unset($javascript[$path]);
}

/**
 * Implementation of template preprocess for the view.
 */
function pixelgarage_preprocess_views_bootstrap_carousel_plugin_style(&$vars) {
  // replace slide with fade
  $count = count($vars['classes_array']);
  $vars['classes_array'][$count-1] = 'carousel carousel-fade';

  // add item attributes (different interval for each slide)
  $view = $vars['view'];
  foreach ($view->result as $index => $entity_object) {
    $node_zitat = $entity_object->_entity_properties['entity object'];
    $duration = $node_zitat->field_lesedauer[LANGUAGE_NONE][0]['value']*1000; // in milliseconds
    $vars['item_attributes'][$index] = drupal_attributes(array('data-interval' => $duration));
  }
}

