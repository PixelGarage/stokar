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

/**
 * Theme function.
 */
function pixelgarage_bootstrap_carousel_if($vars) {
  $files = array();
  foreach ($vars['items'] as $file) {
    if ($vars['background']) {
      $files[] = '<div style="width: ' . check_plain($vars['width']) . '; height: ' . $vars['height'] . '; background-position: ' . $vars['background_pos'] . '; background-size: cover; background-image: url(' . file_create_url($file['uri']) . ');"></div>';
    } else {
      $type = ($vars['image_style']) ? 'image_style' : 'image';
      $file['style_name'] = ($vars['image_style']) ? $vars['image_style'] : '';
      $file['path'] = $file['uri'];
      $files[] = theme($type, $file);
    }
  }
  $filecount = count($files);
  $output = '
      <div id="' . $vars['id'] . '" class="carousel carousel-fade" data-ride="carousel" data-interval="' . $vars['interval'] . '" data-pause="' . $vars['pause'] . '" data-wrap="' . $vars['wrap'] .'" data-keyboard="' . $vars['keyboard'] . '">';
  if ($vars['indicators'] && $filecount > 1) {
    $output .= '<!-- Indicators -->
        <ol class="carousel-indicators">';
    for ($i = 0; $i < $filecount; $i++) {
      if (!$i) {
        $output .= '<li data-target="#' . $vars['id'] . '" data-slide-to="0" class="active"></li>';
      } else {
        $output .= '<li data-target="#' . $vars['id'] . '" data-slide-to="' . $i . '"></li>';
      }
    }
    $output .= '</ol>';
  }

  $output .= '<div class="carousel-inner" role="listbox">';
  // Files/slides
  for ($i = 0; $i < $filecount; $i++) {
    $output .= (!$i) ? '<div class="item active">' : '<div class="item">';
    $output .= $files[$i];
    $output .= '</div>';
  }
  $output .= '</div>';
  if ($filecount > 1) {
    $output .= '<!-- Controls -->
          <a class="left carousel-control" href="#' . $vars['id'] . '" role="button" data-slide="prev">
            <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
            <span class="sr-only">Previous</span>
          </a>
          <a class="right carousel-control" href="#' . $vars['id'] . '" role="button" data-slide="next">
            <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
            <span class="sr-only">Next</span>
          </a>
    ';
  }
  $output .= '</div>';
  return $output;
}

