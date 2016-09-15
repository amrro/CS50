<?php
    
    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if user haven't provide the stock's symbol.
        if (empty($_POST["symbol"]))
        {
            apologize("You must enter quote's symbol!");
        }
        // if user haven't provid the number of share.
        else if (empty($_POST["share"]))
        {
            apologize("You must enter the number of shares you would like to sell!");
        }
        // if symbol wasn't right.
        else if (lookup($_POST["symbol"]) == false)
        {
            apologize("Seems quote symbol is not right!");
        }
        else if (!preg_match("/^\d+$/", $_POST["share"]))
        {
            apologize("please enter non-negative integer for shares.");
        }
        else
        {
            // getting user data (for checking his cash later)
            $user = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
            if (empty($user))
            {
                apologize("Couldn't query your data!");
            }
            
            // getting stock data (price)
            $stock = lookup($_POST["symbol"]);
            
            // compute how much it will cost the user.
            $cost = $stock["price"] * $_POST["share"];

            // if the user can't afford the price
            if ($cost > $user[0]["cash"])
            {
                apologize("You cannot afford that!");
            }
            else 
            {
                // taking cash from user.
                $udpate_cash = CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
                if ($udpate_cash != 1)
                {
                    apologize("failed to update user's cash.");
                }
                else
                {
                    // update portoflios table
                    $udpate_shares = CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
                                    $_SESSION["id"], strtoupper($stock["symbol"]), $_POST["share"]);
                    if ($udpate_shares == false)
                    {
                        apologize("failed to update your portfolio.");
                    }
                    else
                    {
                        // update history table
                        $udpate_history = CS50::query("INSERT INTO `history` (user_id, is_sold, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", 
                                            $_SESSION["id"], 0, strtoupper($stock["symbol"]), $_POST["share"], $stock["price"]);
                        
                        if ($udpate_history != 1)
                        {
                            apologize("failed to update your history.");
                        }
                        else
                        {
                            redirect("index.php");
                        }
                    }
                }
            }
        }
    }
    
?>