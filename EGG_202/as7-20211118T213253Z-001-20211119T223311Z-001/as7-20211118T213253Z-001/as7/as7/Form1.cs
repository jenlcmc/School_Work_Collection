//Names: Uyen Tran & Genaro Grillo
//Task: Windows form application that implements the memory game.
//date: 11/19/2021

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace as7
{
    public partial class Form1 : Form
    {
        //Variables
        PictureBox[,] cards = new PictureBox[4, 5];
        bool[,] cardTurned = new bool[4, 5];
        int[,] cardID = new int[4, 5];
        int matches = 0;
        bool turn = true;
        int lastTunrnedX = 0;
        int lastTurnedY = 0;
        public Form1()
        {
            InitializeComponent();
        }

        private void btnNewGame_Click_Click(object sender, EventArgs e) //Starts the game
        {
            //Card Randomizer
            Random rand = new Random();
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    cards[i, j].Image = Properties.Resources.red_back;
                    cards[i, j].SizeMode = PictureBoxSizeMode.StretchImage;
                   
                }
            }
            //Debugging check box ON
            if(checkBox1.Checked == true)
            {
                int holdAgain = 0;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        cardID[i, j] = holdAgain;
                        holdAgain++;
                    }
                }
            }
           else //Debugging check box OFF
           {
     
                int hold = 0;
          
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            cardID[i, j] = hold;
                            hold++;
                        }
                    }
                for (int i = 0; i < 100; i++)
                {   
                    int x = rand.Next(4);
                    int y = rand.Next(5);
                    int x2 = rand.Next(4);
                    int y2 = rand.Next(5);

                    int temp = cardID[x2, y2];
                    
                    cardID[x2, y2] = cardID[x, y];
                    cardID[x, y] = temp;
                    
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Cards array
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    cards[i, j] = (PictureBox)this.Controls["pictureBox" + (i + 1).ToString() + (j + 1).ToString()];
                    cards[i, j].SizeMode = PictureBoxSizeMode.StretchImage;
                }
            }

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    cards[i, j].Click += Clicked_On_Card;
                }
            }
        }
        
        private async void Clicked_On_Card(object sender, EventArgs e)
        {
            //find indexes 
            PictureBox pictureClicked = (PictureBox)sender;
            string name = pictureClicked.Name.ToString();

            int index = name[name.Length - 2] - '0' - 1;
            int index2 = name[name.Length - 1] - '0' - 1;
           // get card by id
            cards[index, index2].Image = getCardByID(cardID[index, index2]);
            //start of checking cards
            await Task.Delay(2000);
            cards[index, index2].Image = Properties.Resources.red_back;
            cardTurned[index, index2] = false;
            //if card turn then check 
            if (turn == true)
            {
                cardTurned[index, index2] = true;
                lastTurnedY = index2;
                lastTunrnedX = index;
                turn = false;

            }
            // if  card not turn then check for conditions 
            else if (!turn)
            {
                
                    cardTurned[index, index2] = false;
                //dont enable it 
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        cards[i, j].Enabled = false;
                    }
                }
                await Task.Delay(2000);
                //enable the card / reset it
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        cards[i, j].Enabled = true;
                    }
                }
                //recalculate values 
                if (cardID[index, index2] >= 10)
                    {
                        cardID[index, index2] -= 10;

                    }
                    if (cardID[lastTunrnedX, lastTurnedY] >= 10)
                    {
                        cardID[lastTunrnedX, lastTurnedY] -= 10;

                    }
                    //if they are the same 
                    if (cardID[lastTunrnedX, lastTurnedY] == cardID[index, index2])
                    {
                    cards[lastTunrnedX, lastTurnedY].Visible = false;
                        cards[index, index2].Visible = false;
                    turn = true;
                    }
                    // if they are not the same 
                    else
                    {
                        cards[lastTunrnedX, lastTurnedY].Image = Properties.Resources.red_back;
                        cards[index, index2].Image = Properties.Resources.red_back;
                        cardTurned[index, index2] = false;
                        cardTurned[lastTunrnedX, lastTurnedY] = false;
                    }

                
                turn=true;
            }
        }

        private Image getCardByID(int id)
        {   
            //init cards by values 0 -19
            Image img = null;
            switch (id)
            {
                case 0:
                    img = Properties.Resources.AS;
                    break;
                case 1:
                    img = Properties.Resources._2S;
                    break;
                case 2:
                    img = Properties.Resources._3S;
                    break;
                case 3:
                    img = Properties.Resources._4S;
                    break;
                case 4:
                    img = Properties.Resources._5S;
                    break;
                case 5:
                    img = Properties.Resources._6S;
                    break;
                case 6:
                    img = Properties.Resources._10S;
                    break;
                case 7:
                    img = Properties.Resources.JS;
                    break;
                case 8:
                    img = Properties.Resources.QS;
                    break;
                case 9:
                    img = Properties.Resources.KS;
                    break;
                case 10:
                    img = Properties.Resources.AS;
                    break;
                case 11:
                    img = Properties.Resources._2S;
                    break;
                case 12:
                    img = Properties.Resources._3S;
                    break;
                case 13:
                    img = Properties.Resources._4S;
                    break;
                case 14:
                    img = Properties.Resources._5S;
                    break;
                case 15:
                    img = Properties.Resources._6S;
                    break;
                case 16:
                    img = Properties.Resources._10S;
                    break;
                case 17:
                    img = Properties.Resources.JS;
                    break;
                case 18:
                    img = Properties.Resources.QS;
                    break;
                case 19:
                    img = Properties.Resources.KS;
                    break;
               
            }
            return img;
        }

        private void pictureBox1_1_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
