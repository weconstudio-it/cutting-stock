

param W, integer, > 0;
# Input parameter. The width of the master bar.

param M, integer, > 0;
# Input parameter. The number of distinct widths to be cut.


param w{i in 1 .. M}, integer, > 0;
# Input parameter. Defines the widths to be cut.

param b{i in 1 .. M}, integer, > 0;
# Input parameter. b[i] is the minimum number of pieces with width w[i] that need to be cut


####################################################################################################


param K, integer, > 1 :=  sum{i in 1 .. M}  ceil( b[i] / floor(W/w[i]) );
# K is the upper bound of the number of needed bars


var y{k in 1 .. K}, binary;
# y[k] is true if and only if bar k is used in the solution.

var x{i in 1 .. M, k in 1 .. K}, integer, >= 0;
# x[i,k] is the number of cuts of width w[i] produced by the
# cutting pattern of bar k


s.t. satisfy_minimum_required_pieces {i in 1 .. M}:
        sum{k in 1 .. K}  x[i,k]  >=  b[i];
# Make sure the sum of pieces of width w[i] cut by all bars k satisfy the
# minimum requirements b[i].

s.t. do_not_exceed_bar_width {k in 1 .. K}:
    sum{i in 1 .. M}  w[i] * x[i,k]  <=  W * y[k];
# Make sure the sum of widths i cut by bar k do not exceed the master bar's width W,
# if the bar k is used (as defined by the binary variable y[k]).


minimize bars:  sum{k in 1 .. K}  y[k];
# Objective function: minimize the number of bars that need to be cut.


solve;

####################################################################################################

printf "-----------------------------------------------------------------\n";
printf "\n";

printf "Master bar width (W): %d\n", W;
printf "Number of widths to be cut (m): %d\n", M;
printf "\n";

printf "   (width)     (pieces)\n";
for {i in 1 .. M}
{
    printf "    %3i     =>   %3i\n", w[i], b[i];
}
printf "\n";

printf "Total used bars (objective function value): %d\n", bars;
printf "\n";

printf "Generated cutting patterns:\n";
printf "\n";

printf "            ";
for {i in 1 .. M}
{
    printf "%3i  ", w[i];
}
printf "        (selected)\n";

for {j in 1 .. K}
{
    printf "    %3i:  [ ", j;
    for {i in 1 .. M}
    {
        printf "%3i  ", x[i,j];
    }
    printf " ]   =>    %i\n", y[j];
}

printf "  total:    ";
for {i in 1 .. M} {
    printf "%3i  ", sum{k in 1 .. K} x[i,k];
}
printf "\n";

printf "\n";

end;

