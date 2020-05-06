#source grammar

<prog> := <block>

<block> := {<op_list>}

<op_list> := <op><tail>

<op> := <id>=<expr>
	  | <block>

<tail> := ;<op><tail>
         | <epsilon>

<expr> := <ar_expr><relation><ar_exp>
		 | <ar_expr>

<ar_expr> := <ar_exp><sum_op><term>
		    | <term>

<term> := <term><mul_op><factor>
		 |<factor>

<factor> := <id>|<const>|(<ar_expr>)

<relation> := <|<=|==|<>|>|>=

<sum_op> := +|-

<mul_op> := *|/

<id> := $id

<const> = $const





#modified grammar

<prog> := <block>

<block> := {<op_list>}

<op_list> := <op><tail>

<op> := <id>=<expr>
	  | <block>

<tail> := ;<op><tail>
         | <epsilon>

<expr> := <ar_expr><expr'>
		 | <expr'>

<expr> := <relation><ar_exp>
		| <epsilon>

<term> := <mul_op><factor><term'>
		 | <factor>

<term'> := <mul_op><factor><term'>
		 | <mul_op><factor>

<factor> := <id>|<const>|(<ar_expr>)

<relation> := <|<=|==|<>|>|>=

<sum_op> := +|-

<mul_op> := *|/

<id> := $id

<const> = $const



# Modifining grammar 

-- <prog> --> <block>
-- <block> --> <{><op_list><}>
-- <op_list> --> <op><tail>
-- <op> --> <id><=><expr>
-- <tail> --> <;><op><tail>
-- <tail> --> <epsilon>
-- <factor> --> <const>
-- <factor> --> <(><ar_expr><)>
-- <term'> --> <mul_op><factor><term'>
-- <term'> --> <epsilon>
-- <term> --> <const><term'>
-- <term> --> <(><ar_expr><)><term'>
-- <ar_expr'> --> <sum_op><term><ar_expr'>
-- <ar_expr'> --> <epsilon>
-- <ar_expr> --> <const><term'><ar_expr'>
-- <ar_expr> --> <(><ar_expr><)><term'><ar_expr'>
-- <op> --> <{><op_list><}>
-- <term''> --> <epsilon>
-- <term''> --> <epsilon>
-- <term> --> <id><term'><term''>
-- <factor'> --> <epsilon>
-- <factor'> --> <epsilon>
-- <factor> --> <id><factor'>
-- <expr'> --> <relation><ar_expr>
-- <expr'> --> <epsilon>
-- <expr> --> <ar_expr><expr'>
-- <ar_expr''> --> <epsilon>
-- <ar_expr''> --> <epsilon>
-- <ar_expr> --> <id><term'><ar_expr'><ar_expr''>

