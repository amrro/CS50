<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_form.php", ["title" => "Sell"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if user don't provide the stock's symbol.
        if (empty($_POST["symbol"]))
        {
            apologize("You must enter quote's symbol!");
        }
        // if user havn't provid the number of share.
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
            apologize("Your share number is not valid!");
        }
        else
        {
            $share = CS50::query("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            
            // if query return false (means user don't own any shares from this stock).
            if ($share == false)
            {
                apologize("Seems you don't own this stock!");
            }
            else if ($share[0]["shares"] < $_POST["share"])
            {
                apologize("You have only ". $share[0]["shares"] . " shares from this stock!");
            }
            else
            {
                // everything is ok
                // ready to sell the number of shares user would like to sell.
                
                // for getting the most current price
                $stock = lookup($_POST["symbol"]);
                $cash = $stock["price"] * $_POST["share"];
                
                // if user want to sell all shares of this stock,
                if ($share[0]["shares"] == $_POST["share"])
                {
                    // deleting from portofilos table
                    $sold = CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
                    if ($sold != 1)
                    {
                        apologize("failed to sell all of your share!");
                    }
                }
                // if user don't want to sell all shares.
                else if ($share[0]["shares"] > $_POST["share"])
                {
                    $update_share = CS50::query("UPDATE portfolios SET shares = shares - ? WHERE user_id = ? AND symbol = ?", $_POST["share"], $_SESSION["id"], $share[0]["symbol"]);
                    
                    if ($update_share != 1)
                    {
                        apologize ("faild to update your share!");
                    }
                }
                
                    // updating users tables
                    $update_cash = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $cash, $_SESSION["id"]);
                    if ($update_cash != 1)
                    {
                        apologize("failed to update your cash!");
                    }
                    else
                    {
                        // update history table
                        $udpate_history = CS50::query("INSERT INTO `history` (user_id, is_sold, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", 
                                            $_SESSION["id"], 1, strtoupper($share[0]["symbol"]), $_POST["share"], $stock["price"]);
                        
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
    
?>