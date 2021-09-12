--pre UI test
function test1()
	draw_border()

	mvprint(2,0,"Něco sick yo?")
	reverse(true);
	mvprint(1,1,"OK fajn.")
	mvprint(1,5,"Toto je embeded lua interpret 5.3")
	mvprint(1,6,"Prostě OP věc jj yy xd")

	mvprint(7,8,"reverse on")
	reverse(false);
	mvprint(7,10,"reverse off")

	redraw()
	wait_key()
end

-- UI test 1
function test2( )
	add_menu_item("Start/Stop Apache2")
	add_menu_item("Start/Stop TeamSpeak")
	add_menu_item("Reload NIX config")
	add_menu_item("Restart VPS")
	add_menu_item("Shutdown VPS")
	add_menu_item("Shutdown VPS")
	add_menu_item("Shutdown VPS")
	add_menu_item("Shutdown VPS")

	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	add_menu_item("Brekekekeke")
	show_menu()
end

test2()