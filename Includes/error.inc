<?php

//PHP error configuration
error_reporting(E_ALL);
ini_set('log_errors','1');
ini_set('error_log', 'logs/my-errors.log');

//substitute default error handling functions
set_error_handler('error_handler');
set_exception_handler('exception_handler');
register_shutdown_function('fatal_handler');

if($err_cfg = parse_ini_file('error.cfg', TRUE))
{
  $email = $err_cfg['info']['email'];
  $app = $err_cfg['info']['app'];
  $debug = $err_cfg['mode']['debug'];
  $send = $err_cfg['mode']['send'];
  $warning = $err_cfg['mode']['warning'];
  $display = $err_cfg['mode']['display'];
} else //if can't load the configuration file, default to settings that are appropriate for a live project
{
  $email = 'vitor@furlin.me';
  $debug = false;
  $send = true;
  $warning = false;
  $display = false;
  $app = 'App not identified, file:'.__FILE__.' on '.$_SERVER['SERVER_NAME'];
  error_log('App: '.$app.PHP_EOL.'Unable to load file "error.cfg", assuming default values.');
}

ini_set('display_errors', $display);

function error_handler ($type, $message, $file, $line)
{
  global $warning, $debug;
  if(!$warning) if($type == 2) return false;
  if($debug) echo '<pre>Type: '.$type.PHP_EOL.'Message: '.$message.PHP_EOL.'File: '.$file.PHP_EOL.'Line: '.$line.PHP_EOL;
}

function exception_handler ($exception)
{
  echo '<pre>';
  var_dump($exception);
}

//after script execution finishes check for fatal errors
function fatal_handler ()
{
  if ($error = error_get_last())
    switch($error['type'])
    {
        case E_ERROR:
        case E_CORE_ERROR:
        case E_COMPILE_ERROR:
        case E_USER_ERROR:
          error_handler($error['type'], $error['message'], $error['file'], $error['line']);
        break;
    }
}
