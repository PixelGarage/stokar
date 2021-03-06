<?php

/**
 * @file
 * On behalf implementation of Feeds mapping API for date
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 *
 * @see FeedsNodeProcessor::getMappingTargets().
 *
 * @todo Only provides "end date" target if field allows it.
 */
function date_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if (in_array($info['type'], array('date', 'datestamp', 'datetime'))) {
      $targets[$name . ':start'] = array(
        'name' => t('@name: Start', array('@name' => $instance['label'])),
        'callback' => 'date_feeds_set_target',
        'description' => t('The start date for the @name field. Also use if mapping both start and end.', array('@name' => $instance['label'])),
        'real_target' => $name,
      );
      $targets[$name . ':end'] = array(
        'name' => t('@name: End', array('@name' => $instance['label'])),
        'callback' => 'date_feeds_set_target',
        'description' => t('The end date for the @name field.', array('@name' => $instance['label'])),
        'real_target' => $name,
      );
    }
  }
}

/**
 * Callback for setting target values.
 */
function date_feeds_set_target($source, $entity, $target, array $values) {
  list($field_name, $sub_field) = explode(':', $target, 2);

  $delta = 0;
  foreach ($values as $value) {

    if (!($value instanceof FeedsDateTimeElement)) {

      if (empty($value) || !is_numeric($value) && is_string($value) && !date_create($value)) {
        $value = new FeedsDateTimeElement(NULL, NULL);
      }
      elseif ($sub_field == 'end') {
        $value = new FeedsDateTimeElement(NULL, $value);
      }
      else {
        $value = new FeedsDateTimeElement($value, NULL);
      }
    }

    $value->buildDateField($entity, $field_name, $delta);
    $delta++;
  }
}
