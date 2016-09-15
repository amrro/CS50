<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = CS50::query("SELECT * FROM history WHERE user_id = ? ORDER BY order_date", $_SESSION["id"]);
        // dump($rows);
        if ($rows == false)
        {
            apologize("Couldn't retrieve your history");
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
                        "id"   => $row["id"],
                        "name" => $stock["name"],
                        "symbol" => $row["symbol"],
                        "isSold" => ($row["is_sold"]) ? "sell" : "buy",
                        "date" => $row["order_date"],
                        "price" => $row["price"],
                        "shares" => $row["shares"],
                        "total"  => $row["price"] * $row["shares"]
                    ];
                }
            }
        }
        render("history_table.php", ["positions" => $positions, "title" => "History"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
    }
    
?>
