<?php

    require("libphp-phpmailer/class.phpmailer.php");

    // open file
    $handle = fopen("TODO", "r");
    if ($handle == false)
    {
        print("could not open file\n");
        exit(1);
    }

    // array to hold email addresses
    $addresses = [];

    // iterate over rows in file
    while ($row = fgetcsv($handle))
    {
        // name is in first column
        $name = $row[0];
        
        // number is in third column
        $number = $row[2];
        
        // carrier is in fourth column
        $carrier = $row[3];
        
        // determine address
        if ($carrier == "AT&T")
        {
            array_push($addresses, "{$number}@txt.att.net");
        }
        else if ($carrier == "Sprint")
        {
            array_push($addresses, "{$number}@messaging.sprintpcs.com");
        }
        else if ($carrier == "T-Mobile")
        {
            array_push($addresses, "{$number}@tmomail.net");
        }
        else if ($carrier == "Verizon")
        {
            array_push($addresses, "{$number}@vtext.com");
        }
        else if ($carrier == "Virgin Mobile")
        {
           array_push($addresses, "{$number}@vmobl.com");
        }
    }

    // close file
    fclose($handle);
    
    // instantiate mailer
    $mail = new PHPMailer();

    // configure mailer
    // http://phpmailer.worxware.com/index.php?pg=methods
    // http://phpmailer.worxware.com/index.php?pg=properties
    // https://www.google.com/settings/u/0/security/lesssecureapps
    $mail->IsSMTP();
    $mail->Host = "smtp.gmail.com";
    $mail->Password = "TODO";
    $mail->Port = 587;
    $mail->SMTPAuth = true;
    $mail->SMTPDebug = 1;
    $mail->SMTPSecure = "tls";
    $mail->Username = "TODO";

    // set From:
    $mail->SetFrom("bot@cs50.net");

    // set body
    $mail->Body = "Miss you! love, CS50 Bot";

    // iterate over email addresses
    for ($i = 0, $n = count($addresses); $i < $n; $i++)
    {
        // add email address to To: field
        $mail->addAddress($addresses[$i]);

        // send email
        if ($mail->Send())
        {
            print("Sent text #{$i}.\n");
        }
        else
        {
            print($mail->ErrorInfo);
        }

        // clear To: field
        $mail->ClearAddresses();
    }
    
?>
