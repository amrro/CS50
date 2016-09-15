<div class="alert alert-success" role="alert">
    <h4>History ordered by date</h4>
</div>

<table class="table table-hover table-bordered">
    <thead class="thead-default">
        <tr>
            <td><b>#</b></td>
            <td><b>NAME</b></td>
            <td><b>SYMBOL</b></td>
            <td><b>SELL/BUY</b></td>
            <td><b>DATE</b></td>
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
                    print("<td>" . $position["id"] . "</td>");
                    print("<td>" . $position["name"] . "</td>");
                    print("<td>" . strtoupper($position["symbol"]) . "</td>");
                    print("<td>" . $position["isSold"] . "</td>");
                    print("<td>" . $position["date"] . "</td>");
                    print("<td>" . $position["shares"] . "</td>");
                    print("<td>" . number_format($position["price"], 2, ".", ",") . "</td>");
                    print("<td>" . number_format($position["total"], 2, ".", ",") . "</td>");
                    print("</tr>");
                }
        
            ?>
    <tbody>
</table>