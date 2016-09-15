<?php

    // configuration
    require("../includes/config.php"); 
    
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $user = CS50::query("SELECT username, cash FROM users WHERE id = ?", $_SESSION["id"]);
    
    if ($rows == false || $user == false)
    {
        apologize("Errors happen!");
    }
    else
    {
        $positions = [];
    
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            
            if ($stock !== false)
            {
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"]
                ];
            }
        }
    }


    // render portfolio
    render("portfolio.php", ["positions" => $positions, "user" => $user, "title" => "Portfolio"]);

?>
