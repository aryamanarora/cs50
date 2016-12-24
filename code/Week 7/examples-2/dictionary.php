<?php

  $size = 0; // hey that's what I did!
  $table = []; // a hash table, what...

  function size() // easy enough
  {
    global $size;
    return $size;
  }

  function load($dictionary) // no return type
  {
    $lines = file($dictionary); // EVERY LINE
    foreach ($lines as $line)
    {
      $table[$line] = true;
    }
  }

  function check($word)
  {
    if ($table[$word] == true)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  function unload()
  {
    return; // seriously
  }

?>
