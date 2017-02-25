#pragma once

class Figure
{
protected:
public:
	int x1,y1,x2,y2,type;
	int pid,id,action;
	COLORREF Lcolor,Bcolor;
	Figure(void);
	Figure(int xx1,int yy1, int xx2, int yy2,COLORREF NBcolor,COLORREF NLcolor,int Naction,int Npid,int Ni)
	{
		x1=xx1;
		x2=xx2;
		y1=yy1;
		y2=yy2;
		type=0;
		Bcolor=NBcolor;
		Lcolor=NLcolor;
		action=Naction;
		pid=Npid;
		id=Ni;
	}
	Figure(int xx1,int yy1, int xx2, int yy2,COLORREF NBcolor,COLORREF NLcolor)
	{
		x1=xx1;
		x2=xx2;
		y1=yy1;
		y2=yy2;
		type=0;
		Bcolor=NBcolor;
		Lcolor=NLcolor;
		action=0;
		pid=0;
		id=0;
	}	
	virtual void Draw(CDC *dc)=0;
	virtual ~Figure(void);
};

class RectangleM : public Figure{
public:
	RectangleM(int xx1,int yy1, int xx2, int yy2,COLORREF NBcolor,COLORREF NLcolor,int Naction,int Npid,int Ni)
		:Figure(xx1,yy1,xx2,yy2,NBcolor,NLcolor,Naction,Npid,Ni)
	{
	type=1;
	
	}
	RectangleM(int xx1,int yy1, int xx2, int yy2,COLORREF NBcolor,COLORREF NLcolor)
		:Figure(xx1,yy1,xx2,yy2,NBcolor,NLcolor)
	{
	type=1;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush(Bcolor);
		CPen myPen(PS_SOLID, 3, Lcolor);
		
		CBrush *oldBrush;
		CPen *oldPen;
		
		oldBrush = dc->SelectObject(&myBrush);
		oldPen= dc->SelectObject( &myPen );	
		
		dc->Rectangle(x1,y1,x2,y2); //draw
		
		dc->SelectObject( oldPen ); 
		dc->SelectObject(oldBrush);
	}
};
class EllipseM:public RectangleM{
public:
	EllipseM(int xx1,int yy1, int xx2, int yy2,COLORREF NBcolor,COLORREF NLcolor)
		:RectangleM(xx1,yy1,xx2,yy2,NBcolor,NLcolor)
	{
	type=2;
	}
	EllipseM(int xx1,int yy1, int xx2, int yy2,COLORREF NBcolor,COLORREF NLcolor,int Naction,int Npid,int Ni)
		:RectangleM(xx1,yy1,xx2,yy2,NBcolor,NLcolor,Naction,Npid,Ni)
	{
	type=2;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush(Bcolor);
		CPen myPen(PS_SOLID, 3, Lcolor);
		
		CBrush *oldBrush;
		CPen *oldPen;
		
		oldBrush = dc->SelectObject(&myBrush);
		oldPen= dc->SelectObject( &myPen );	

		dc->Ellipse(x1,y1,x2,y2);; //draw
		
		dc->SelectObject( oldPen ); 
		dc->SelectObject(oldBrush);
	}
};


class LineM:public Figure{
public:
	LineM(int xx1,int yy1, int xx2, int yy2,COLORREF NBcolor,COLORREF NLcolor)
		:Figure(xx1,yy1,xx2,yy2,NBcolor,NLcolor)
	{
	type=3;
	}
	LineM(int xx1,int yy1, int xx2, int yy2,COLORREF NBcolor,COLORREF NLcolor,int Naction,int Npid,int Ni)
		:Figure(xx1,yy1,xx2,yy2,NBcolor,NLcolor,Naction,Npid,Ni)
	{
	type=3;
	}
	
	void Draw(CDC *dc)
	{
		CBrush myBrush(Bcolor);
		CPen myPen(PS_SOLID, 3, Lcolor);
		
		CBrush *oldBrush;
		CPen *oldPen;
		
		oldBrush = dc->SelectObject(&myBrush);
		oldPen= dc->SelectObject( &myPen );	


		

		dc->MoveTo(x1,y1);
		dc->LineTo(x2,y2);


				dc->SelectObject( oldPen ); 
		dc->SelectObject(oldBrush);


	}

};


