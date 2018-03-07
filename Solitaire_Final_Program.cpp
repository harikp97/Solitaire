//Solitaire by Viraj Karambelkar and Harikrishnan KP.The suits are not mentioned in the game.


#include<simplecpp>
bool isClicked=false;
bool isValid=false;
int deckofcards[52];//stores the deck of cards which will be used in a game.


void initialize(int *deckofcards)   //function to initialize the deck to be used randomly
{
    for(int i=0;i<52;i++)
    {
        *(deckofcards+i)=(i/13+1)*100+i%13+1;

    }
}


Rectangle createcard(int x,int y,int b)
{
    Rectangle r(x,y,120,b);
    r.setColor(COLOR("red"));
    r.setFill(true);
    return r;
}

char text(int z)
{
    char c;
    if(z%100==1) c='A';
    else if(z%100==2) c='2';
    else if(z%100==3) c='3';
    else if(z%100==4) c='4';
    else if(z%100==5) c='5';
    else if(z%100==6) c='6';
    else if(z%100==7) c='7';
    else if(z%100==8) c='8';
    else if(z%100==9) c='9';
    else if(z%100==10) c='0';
    else if(z%100==11) c='J';
    else if(z%100==12) c='Q';
    else if(z%100==13) c='K';
    return c;
}
void reveal(Rectangle &r,int z,Text &T)
{
    int x=r.getX();
    int y=r.getY();
    int n=0;
    while((120-n)>=0)
    {
        r.reset(x,y,120-n,180);
        n=n+20;
        wait(0.01);

    }


    r.setFill(false);
    char c=text(z);
    if(c=='J')  T.reset(r.getX()-55,r.getY()-80,"J");
    else if(c=='Q')  T.reset(r.getX()-55,r.getY()-80,"Q");
    else if(c=='K') T.reset(r.getX()-55,r.getY()-80,"K");
    else if(c=='A') T.reset(r.getX()-55,r.getY()-80,"A");
    else if(c=='0') T.reset(r.getX()-55,r.getY()-80,"10");
    else  T.reset(r.getX()-55,r.getY()-80,c-'0');


    if(z/100==1)
    {
        T.setColor(COLOR("black"));
    }
    else if(z/100==2)
    {
        T.setColor(COLOR("red"));
    }
    else if(z/100==3)
    {
        T.setColor(COLOR("black"));
    }
    else if(z/100==4)
    {
        T.setColor(COLOR("red"));
    }


    while((120-n)>=-120)
    {
        r.reset(x,y,120-n,180);
        n=n+20;
        wait(0.01);
    }

}

class bottomstack
{
public:
Rectangle r[13];
int a[13];
Text txt[13];
public:
signed int pos=0;

bool check(bottomstack &y,int x)                     //function to check if the desired move is valid
{
    if(y.pos+1==0&& x%100==13)
        return true;

    if (abs((y.a[y.pos]/100)-(x/100))==2)
        return false;
    if(y.a[y.pos]%100-x%100==1)
        return true;
    else
        return false;
}



void moveTo(bottomstack &b,bottomstack &t)                //accepts an array of cards and includes it in the target stack
{
for(int i=0;i<=t.pos;i++)
{
b.pos++;
b.a[b.pos]=t.a[i];
b.r[b.pos]=t.r[i];
b.txt[b.pos]=t.txt[i];
t.r[i].reset(0,0,0,0);
t.txt[i].reset(0,0,"");
}
}


void crdmove(int j,bottomstack &m,int fin,int in)               //finction to move 'j' number of cards from one stack to the other
{

int ptr=pos-j+1;
bottomstack temp;
int i=0;
if (check(m,a[ptr]))
{

repeat(25)
{
for(i=0;i<j;i++)
{

    r[ptr+i].move(((fin-in)*140)/25.0,0);
    txt[i+ptr].move(((fin-in)*140)/25.0,0);
}


}

repeat(25)
{
    for(i=0;i<j;i++)
{
    r[i+ptr].move(0,(m.pos+1-pos+j-1)*20/25.0);
    txt[i+ptr].move(0,(m.pos+1-pos+j-1)*20/25.0);
}
}
i=0;
for(int k=ptr;k<=pos;k++)
{
temp.a[i]=a[k];
temp.r[i]=r[k];
temp.txt[i]=txt[k];
r[k].reset(0,0,0,0);
txt[k].reset(0,0,"");
i++;
}



temp.pos=j-1;
pos=ptr-1;
moveTo(m,temp);


if(m.pos>=j)
{
        m.r[m.pos-j].reset(m.r[m.pos-j].getX(),m.r[m.pos-j].getY()-80,120,20);
}

if(pos>=0)
{
    r[pos].reset(r[pos].getX(),r[pos].getY()+80,120,180);
    reveal(r[pos],a[pos],txt[pos]);
}

}
}
};
class lefttop1{                         //left up pile which the user will click

    public:
    int cards[24];
    int number=24;
    int topcard=0;
    Rectangle r[24];
    Text t[24];
    //bool isLast=false;

    void display()
    {
        /*if(isLast)
        {

            for(int i=0;i<=number;i++)
            {
                r[i].reset(0,0,0,0);
            }

        }*/
        /*if(topcard==number-1)
       {

           isLast=true;
           r[topcard]=createcard(80,140,180);
            r[topcard].move(140,0);
            reveal(r[topcard],cards[topcard],t[topcard]);
       }

       else*/

            r[topcard]=createcard(80,140,120);
            r[topcard].move(140,0);
            reveal(r[topcard],cards[topcard],t[topcard]);


       topcard=(topcard+1)%number;

    }

    lefttop1()      //will initialize this right top pile with first 24 cards from deck
    {
        for (int i=0;i<24;i++)
        {
            cards[i]=deckofcards[i];
        }
    }
    bool check(bottomstack &m)
    {
        if(m.pos+1==0 && cards[topcard-1]%100==13)
        return true;

        if((m.a[m.pos]/100)-(cards[topcard-1]/100)==2|| (m.a[m.pos]/100)-(cards[topcard-1]/100)==0)
        return false;

        if(abs((m.a[m.pos]%100)-(cards[topcard-1]%100)==1))
        return true;

        else
        return false;
    }
    void cmove(bottomstack &m,int in,int fin)
    {
        if(check(m))
        {

        m.a[++m.pos]=cards[topcard-1];



        repeat(25)
        {
            cout<<"Yeah";
           r[topcard-1].move(((fin-in)*140)/25.0,0);
           t[topcard-1].move(((fin-in)*140)/25.0,0);
        }
        repeat(25)
        {
            r[topcard-1].move(0,(230+m.pos*20)/25.0);
            t[topcard-1].move(0,(230+m.pos*20)/25.0);
        }

        m.r[m.pos-1].reset(m.r[m.pos-1].getX(),m.r[m.pos-1].getY()-80,120,20);
        m.r[m.pos]=r[topcard-1];
        m.txt[m.pos]=t[topcard-1];
        r[topcard-1].reset(0,0,0,0);
        t[topcard-1].reset(0,0,"");

        for(int i=topcard-1;i<number-1;i++)
        {
            cards[i]=cards[i+1];
            r[i]=r[i+1];
            t[i]=t[i+1];
        }
        number-=1;
        topcard-=1;
        }


    }

    void cremove()
    {
        for(int i=topcard-1;i<number-1;i++)
        {
            cards[i]=cards[i+1];
        }
        number-=1;
        topcard-=1;

    }
};

class topright                          //right top card stack where accumulation takes place
{
    public:

    int s=100;
    int h=200;
    int c=300;
    int d=400;
    Rectangle r1,r2,r3,r4;
    Text t1,t2,t3,t4;


    void cbmove(Rectangle &r,int card,int fin,Text &t)
    {
    bool valid=false;
        if(fin==3 && (card-s)==1)
        {
        s=card;
        valid= true;
        }


        if(fin==4 && (card-h)==1)
        {
        h=card;
        valid=true;
        }

        if(fin==5 &&(card-c)==1)
        {
        c=card;
        valid=true;
        }

      if(fin==6 && (card-d)==1)
        {
        d=card;
        valid=true;
        }

        if(valid)
        {
        repeat(25)
        {
            r.move((fin-1)*140/25.0,0);
            t.move((fin-1)*140/25.0,0);
        }
        if(fin==3)
        {
            r1=r;
            t1=t;
            r.reset(0,0,0,0);
            t.reset(0,0,"");
        }

        if(fin==4)
        {
            r2=r;
            t2=t;
            r.reset(0,0,0,0);
            t.reset(0,0,"");
        }

        if(fin==5)
        {
            r3=r;
            t3=t;
            r.reset(0,0,0,0);
            t.reset(0,0,"");
        }

        if(fin==6)
        {
            r4=r;
            t4=t;
            r.reset(0,0,0,0);
            t.reset(0,0,"");
        }
        }
    }

    void camove(int card,int in,int fin,bottomstack &z)
    {
    bool valid=false;

        if(fin==3 && (card-s)==1)
        {
        s=card;
        valid= true;
        }


        if(fin==4 && (card-h)==1)
        {
        h=card;
        valid=true;
        }

        if(fin==5 &&(card-c)==1)
        {
        c=card;
        valid=true;
        }

      if(fin==6 && (card-d)==1)
        {
        d=card;
        valid=true;
        }


if(valid)
{
repeat(25)
{

    z.r[z.pos].move((420+(fin-in-3)*140)/25.0,0);
    z.txt[z.pos].move((420+(fin-in-3)*140)/25.0,0);
}
repeat(25)
{
    z.r[z.pos].move(0,(-230-z.pos*20)/25.0);
    z.txt[z.pos].move(0,(-230-z.pos*20)/25.0);
}

if(fin==3)
{
    r1=z.r[z.pos];
    t1=z.txt[z.pos];
    z.r[z.pos].reset(0,0,0,0);
    z.txt[z.pos].reset(0,0,"");
}
else if(fin==4)
{
    r2=z.r[z.pos];
    t2=z.txt[z.pos];
    z.r[z.pos].reset(0,0,0,0);
    z.txt[z.pos].reset(0,0,"");
}
else if(fin==5)
{
    r3=z.r[z.pos];
    t3=z.txt[z.pos];
    z.r[z.pos].reset(0,0,0,0);
    z.txt[z.pos].reset(0,0,"");
}
else if(fin==6)
{
    r4=z.r[z.pos];
    t4=z.txt[z.pos];
    z.r[z.pos].reset(0,0,0,0);
    z.txt[z.pos].reset(0,0,"");
}
z.pos--;

if (z.pos>=0)
{
    z.r[z.pos].reset(z.r[z.pos].getX(),z.r[z.pos].getY()+80,120,180);
    reveal(z.r[z.pos],z.a[z.pos],z.txt[z.pos]);
}
}
    }
};







int detectclick()
{
int row=0,col=0;
int w=getClick();
int x=w/65536;
int y=w%65536;
if(x>20&&x<140)
col=1;
else if(x>160&&x<280)
col=2;
else if(x>300&&x<420)
col=3;
else if(x>440&&x<560)
col=4;
else if(x>580&&x<700)
col=5;
else if(x>720&&x<840)
col=6;
else if(x>860&&x<980)
col=7;

if(y>50&&y<230)
row=100;
else if(y>280&&y<300)
row=201;
else if(y>300&&y<320)
row=202;
else if(y>320&&y<340)
row=203;
else if(y>340&&y<360)
row=204;
else if(y>360&&y<380)
row=205;
else if(y>380&&y<400)
row=206;
else if(y>400&&y<420)
row=207;
else if(y>420&&y<440)
row=208;
else if(y>440&&y<460)
row=209;
else if(y>460&&y<480)
row=210;
else if(y>480&&y<500)
row=211;
else if(y>500&&y<520)
row=212;
else if(y>520&&y<540)
row=213;
if(row*col==0)
return 0;
else if(row==100&&col==3)
return 0;
return col*1000+row;
}


#include<simplecpp>
int main()
{
initCanvas("Solitaire",1000,900);
initialize(&deckofcards[0]);
bottomstack t[7];
topright tr;
lefttop1 lt;


int j=24;
for(int i=1;i<8;i++)
{
for(int k=0;k<i;k++)
{
t[i-1].a[k]=deckofcards[j++];
t[i-1].pos++;
}
t[i-1].pos--;
}

for(int i=0;i<7;i++)
{
    cout<<t[i].a[t[i].pos]<<" "<<t[i].pos;
}


for(int i=1;i<8;i++)
{
if(i==3)
continue;
Rectangle r1(80+140*(i-1),140,120,180);
r1.setColor(COLOR("red"));
r1.setFill(false);
r1.imprint();
}


for(int i=0;i<7;i++)
{
    for(j=0;j<i;j++)
    {
    t[i].r[j]=createcard(80+i*140,290+j*20,20);

    }
    t[i].r[j]=createcard(80+i*140,370+j*20,180);
    reveal(t[i].r[j],t[i].a[t[i].pos],t[i].txt[j]);
}

int p,q,q1,q2,p1,p2;

while(tr.s!=113 && tr.h!=213 && tr.d!=313 && tr.c!=413)
{
     q=detectclick();
     q1=q/1000;
     q2=q%1000;
    if((q2>200)&&((q2-200)>t[q1-1].pos+1))
    q2=200+t[q1-1].pos+1;
    q=q1*1000+q2;
    if(q==0)
    {
        isClicked=false;
        continue;
    }

    isClicked=true;


    if(q1==1&&q2==100)
     {
        lt.display();
        isClicked=false;
        continue;
     }

     else if(q==2100)
     {
        p=detectclick();
        p1=p/1000;
        p2=p%1000;
        if((p2>200)&&((p2-200)>t[p1-1].pos+1))
        p2=200+t[p1-1].pos+1;
        p=p1*1000+p2;
        if(p==0)
        {
        isClicked=false;
        continue;
        }

        else if(p2/100==2)
        {
        lt.cmove(t[p1-1],q1-1,p1-1);
        isClicked=false;
        continue;
        }

        else if(p2/100==1)
        {
        tr.cbmove(lt.r[lt.topcard-1],lt.cards[lt.topcard-1],p1-1,lt.t[lt.topcard-1]);
        isClicked=false;
        continue;
        }
     }

    else if(q2/100==2)
    {
     p=detectclick();
     p1=p/1000;
     p2=p%1000;
    if((p2>200)&&((p2-200)>t[p1-1].pos+1))
    p2=200+t[p1-1].pos+1;
    p=p1*1000+p2;

    if(p==0)
    {
    isClicked=false;
    continue;
    }



        if(p2/100==2)
        {
            if((t[p1-1].pos+1)!=p2%200)
            {
            isClicked=false;
            continue;
            }
            else
            {
            t[q1-1].crdmove(t[q1-1].pos+2-q2%200,t[p1-1],p1-1,q1-1);

            }
        }

        else if(p==4100|| p==5100|| p==6100|| p==7100)
        {
        tr.camove(t[q1-1].a[q2%200-1],q1-1,p1-1,t[q1-1]);
        }
        isClicked=false;
    }


    }
}
