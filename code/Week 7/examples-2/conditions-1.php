<?php

  $n = readline("I'd like an integer please: ");

  if ($n > 0)
  {
    printf("You picked a positive number\n");
  }
  else if ($n == 0)
  {
    printf("You picked 0\n");
  }
  else
  {
    printf("You picked a negative number\n");
  }

?>
