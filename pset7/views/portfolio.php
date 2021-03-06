<div class="alert alert-success" role="alert">
    <h4 class="alert-heading">Hello, <?= $user[0]["username"]?></h4>
    <h4>Your current cash is <kbd><b>$<?= number_format($user[0]["cash"], 2, ".", ",")?></b></kbd></h4>
</div>

<table class="table table-hover table-bordered">
    <thead class="thead-default">
        <tr>
            <td><b>SYMBOL</b></td>
            <td><b>NAME</b></td>
            <td><b>SHARES</b></td>
            <td><b>PRICE ($)</b></td>
            <td><b>TOTAL ($)</b></td>
        </tr>
    </thead>
    
    <tbody>
        <?php
        
                foreach ($positions as $position)
                {
                    print("<tr>");
                    print("<td>" . strtoupper($position["symbol"]) . "</td>");
                    print("<td>" . $position["name"] . "</td>");
                    print("<td>" . $position["shares"] . "</td>");
                    print("<td>" . $position["price"] . "</td>");
                    print("<td>" . number_format($position["price"] * $position["shares"], 2, ".", ",") . "</td>");
                    print("</tr>");
                }
        
            ?>
    <tbody>
</table>