<?php
$settings = parse_ini_file('Includes/database.cfg', TRUE);

$dns = $settings['connection']['driver'].':host=' . $settings['dns']['host'].';port=' . $settings['dns']['port'].';dbname=' . $settings['dns']['dbname'];

$options = array(
  PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES UTF8',
  PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION
);

$pdo_connection = new PDO($dns, $settings['connection']['user'], $settings['connection']['pass'], $options);
