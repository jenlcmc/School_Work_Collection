/*Name = Genaro Grillo & Uyen Tran                  
 * Section = 1004 & 1006 
 * Description: implement a tic tac toe game. 
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab6
{
    public partial class Form1 : Form
    {
        //Variables
        bool winner = false;
        bool player = true;
        int turns = 0;
        Button[] buttons = new Button[9];

        public Form1()
        {
            InitializeComponent();
        }

        //Array the buttons
        private void Form1_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < buttons.Length; i++)
                buttons[i] = (Button)this.Controls["btn" + (i + 1).ToString()];

            foreach (Button btn in buttons)
                btn.Text = "";
            //Starting turn
            lblturn.Text = "Player X's turn";

        }

        private void button_clicked(Object sender, EventArgs e) //When you click the any buttom
        {
            //Check if the button is already pressed
            if (((Button)sender).Text == "")
            {
                
                if (player == true)   //X's turn
                {
                    ((Button)sender).ForeColor = Color.Red;
                    ((Button)sender).Text = "X";
                    lblturn.Text = "Player O's turn";
                }
                else                  //O's turn
                {
                    ((Button)sender).ForeColor = Color.Black;
                    ((Button)sender).Text = "O";
                    lblturn.Text = "Player X's turn";
                }
                //Change player's turn
                player = !player;
                //Add a turn played out of 9 possible
                turns++;
                //Go to checker function
                checker();
            }

        }
        private void checker() //Find out who is the winner
        {
            //Turn off Play Again button until the game finishes
            plyagain.Enabled = false;

            //Horizontal Checks
            if ((btn1.Text == btn2.Text) && (btn2.Text == btn3.Text) && (btn1.Text != ""))
                winner = true;
            else if ((btn4.Text == btn5.Text) && (btn5.Text == btn6.Text) && (btn4.Text != ""))
                winner = true;
            else if ((btn7.Text == btn8.Text) && (btn8.Text == btn9.Text) && (btn7.Text != ""))
                winner = true;

            //Verical checks
            else if ((btn1.Text == btn4.Text) && (btn4.Text == btn7.Text) && (btn1.Text != ""))
                winner = true;
            else if ((btn2.Text == btn5.Text) && (btn5.Text == btn8.Text) && (btn2.Text != ""))
                winner = true;
            else if ((btn3.Text == btn6.Text) && (btn6.Text == btn9.Text) && (btn3.Text != ""))
                winner = true;

            //Cross checks
            else if ((btn1.Text == btn5.Text) && (btn5.Text == btn9.Text) && (btn1.Text != ""))
                winner = true;
            else if ((btn3.Text == btn5.Text) && (btn5.Text == btn7.Text) && (btn3.Text != ""))
                winner = true;


            if (winner == true) //If someone wins
            {
                String whowon = "";
                if (player == true) // Set up winner to O
                {
                    whowon = "O";
                    owin.Text = (Int32.Parse(owin.Text) + 1).ToString();
                    Disable();
                }
                else               // Set up winner to X
                {
                    whowon = "X";
                    xwin.Text = (Int32.Parse(xwin.Text) + 1).ToString();
                    Disable();
                    plyagain.Enabled = true;
                }
                MessageBox.Show("Player " + whowon + " Wins!");
                plyagain.Enabled = true;
            }
            
            else                //If no one wins
            {
                if (turns == 9)
                {
                    MessageBox.Show("Draw!");
                    draw.Text = (Int32.Parse(draw.Text) + 1).ToString();
                    Disable();
                    plyagain.Enabled = true;
                }
            }           
        }
        private void Disable() // Blocking buttons from being used again
        {
            if (winner == true)
            {
                try
                {
                    foreach (Button btn in buttons)
                        btn.Enabled = false;
                }
                catch { }
            }
            else if (turns == 9)
            {
                try
                {
                    foreach (Button btn in buttons)
                        btn.Enabled = false;
                }
                catch { }
            }
        }

        private void plyagain_Click(object sender, EventArgs e) //Restart the game
        {
            //Restart turns, count and set up the turn back to X and set up the winner variable back to false
            player = true;
            turns = 0;
            winner = false;
            lblturn.Text = "Player X's turn";

            //Clear buttons
            foreach (Button btn in buttons) 
            {
                btn.Enabled = true;
                btn.Text = "";
            }


        }

        private void quitprogram_Click(object sender, EventArgs e) //Closes the program
        {
            Application.Exit();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
