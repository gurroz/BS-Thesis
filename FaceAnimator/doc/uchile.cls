%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Clase para formatear las tesis, memorias o trabajos de 
% titulo de la Universidad de Chile
% Autor: Sebastian Kreft C.
% v0.01 31/08/2007
% http://www.dcc.uchile.cl/~skreft/tesis
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{uchile}[ 2007/08/31 Tesis Universidad de Chile ]


%% Cargamos los paquetes necesarios
\RequirePackage{graphicx} %necesario para incluir el escudo de la universidad
\RequirePackage{multirow} %necesario para insertar bien el logo
%no se como hacer para que funcionen los margenes desde esta clase
%\RequirePackage{anysize}
%\papersize{21.5cm}{28.0cm}
%\marginsize{3.0cm}{2.0cm}{2.0cm}{2.0cm}
% Fijamos los margenes
%\usepackage[top=0cm, bottom=0cm, left=0cm, right=0cm]{geometry} 
%\setlength{\voffset}{0cm}	
%\setlength{\hoffset}{0cm}	
%\setlength{\oddsidemargin}{0.0cm}	
%\setlength{\evensidemargin}{0.0cm}	
%\setlength{\topmargin}{0.0cm}		
%\setlength{\textwidth}{14.0cm}		
%\setlength{\textheight}{21.5cm}		
%\setlength{\marginparsep}{0cm}

%  Tesis se parace mucho a un report

%agregar todos los tipos de papeles distintos a letterpaper
\DeclareOption{a4paper}{\ClassError { uchile } { Papel A4 no es valido para las tesis } { Indicar letterpaper en las opciones del docuemento o no asignar ningun papel  }}
\DeclareOption{legalpaper}{\ClassError { uchile } { Papel Legal no es valido para las tesis } { Indicar letterpaper en las opciones del documento o no asignar ningun papel  }}
\DeclareOption{bw}{\gdef\@logofile{escudo.png}}
\DeclareOption{color}{\gdef\@logofile{escudocolor.png}}
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{report}}
\ExecuteOptions{bw}
\ProcessOptions\relax
\LoadClass{report}

%% Definimos nuevos comandos para definir la portada
\newcommand{\departamento}{\gdef\@departamento}
\newcommand{\facultad}{\gdef\@facultad}
\newcommand{\universidad}{\gdef\@universidad}
\newcommand{\trabajoygrado}{\gdef\@trabajoygrado}
\newcommand{\pais}{\gdef\@pais}
\newcommand{\ciudad}{\gdef\@ciudad}
\newcommand{\yearpub}{\gdef\@year}
\newcommand{\monthpub}{\gdef\@month}
\newcommand{\profguia}{\gdef\@profguia}
\newcommand{\profcom}{\gdef\@profcom}
\newcommand{\profco}{\gdef\@profco}
\newcommand{\profint}{\gdef\@profint}

\renewcommand{\maketitle}{%
\thispagestyle{empty}
\renewcommand{\baselinestretch}{1}
\begin{tabular}{ll}
\multirow{5}{*}{\includegraphics[height=84pt,width=42pt]{\@logofile}}&\\
&\\
&\large{\MakeUppercase{\@universidad}}\\
&\large{\MakeUppercase{\@facultad}}\\
&\large{\MakeUppercase{\@departamento}}\\
\end{tabular}

%\includegraphics[height=84pt,width=42pt]{\@logofile}
%\includegraphics[height=84pt,width=42pt]{escudo.png}
\begin{center}
%{\large \MakeUppercase{\@universidad} \\
%\MakeUppercase{\@facultad}\\
%\MakeUppercase{\@departamento}\\}

%\hrulefill

\vskip 3cm%
{\Large \MakeUppercase{\@title} }\\
\vskip 1cm%
\MakeUppercase{\@trabajoygrado}\\
\vskip 1.5cm%
\MakeUppercase{\@author}\\
\vskip 3.0cm%
%\hrulefill
%\\
\MakeUppercase{Profesor gu\'ia:}\\
\MakeUppercase{\@profguia}\\
\vskip 0.5cm%
\MakeUppercase{Miembros de la comisi\'on:}\\
{\MakeUppercase \@profcom}\\
{\MakeUppercase \@profint}\\
\vskip 2.5cm%
\MakeUppercase{\@ciudad{} de \@pais}\\
\MakeUppercase{\@month{} \@year}
\end{center}
\newpage
}
%\renewcommand{\chapter}[1]{\chapter{\MakeUppercase{#1}}}
%\newcommand{\preamble}{\pagenumbering{Roman}}
%\newcommand{\text}{\pagenumbering{arabic}}

%% Definimos espacio a doble linea
%\renewcommand{\baselinestretch}{2}

%% Le cambiamos el nombre a toc
\let\oldtableofcontents=\tableofcontents
\renewcommand{\tableofcontents}{
	\renewcommand{\contentsname}{Tabla de Contenidos}
	\oldtableofcontents
}
%% Cambiamos section cuando estamos en el prefacio
\let\oldsection=\section
\let\oldthesection=\thesection
\newenvironment{preface}{
        \pagenumbering{roman}
        \pagestyle{plain}
		\renewcommand{\section}[1]{%
    	    \chapter*{##1}
    	    \addcontentsline{toc}{chapter}{##1}
		}
}{
		\newpage
    %    \tableofcontents
    %    \iftablespage
    %            \listoftables
    %    \fi
    %    \iffigurespage
    %            \listoffigures
    %    \fi
    %    \cleardoublepage
        \pagenumbering{arabic}
        \pagestyle{headings}
		\let\section=\oldsection
}
%ver que pasa cuando no se entregan todos los paramteros%
\newcommand{\makeeval}{%
%\thispagestyle{empty}
\renewcommand{\baselinestretch}{1}
\begin{center}
{\large \MakeUppercase{\@universidad} \\
\MakeUppercase{\@facultad}\\
\MakeUppercase{\@escuela}\\}
\vskip 2em%
{\Large \MakeUppercase{\@title} }\\
\vskip 2em%
\MakeUppercase{\@author}\\
\end{center}
\vskip 2em%
\begin{tabular}{lccc}
COMISI\'ON & NOTA & CALIFICACIONES & FIRMA \\
EXAMINADORA & (n) & (letras) &  \\
PROFESOR GU\'IA& & & \\
\MakeUppercase{\@profguia} & .........&.............&.............\\
PROFESOR CO-GU\'IA & & & \\
\MakeUppercase{\@profco} & .........&.............&.............\\
PROFESOR INTEGRANTE & & & \\
\MakeUppercase{\@profint} & .........&.............&.............\\
\end{tabular}
\begin{center}
\@trabajoygrado\\
\vskip 2em%
\@ciudad, \@pais.\\
\@year
\end{center}
\newpage
}

%%definimos un ambiente para los apendices
\newenvironment{appendix2}{
	\chapter*{Ap\'endices}
   	   \addcontentsline{toc}{chapter}{Apéndices}
       % \pagenumbering{roman}
        %\pagestyle{plain}
		%\renewcommand{\section}[1]{%
    	%    \oldsection{##1}
		%}
	\renewcommand{\thesection}{
		\Alph{section}
	}
}{
	%	\newpage
    %    \tableofcontents
    %    \iftablespage
    %            \listoftables
    %    \fi
    %    \iffigurespage
    %            \listoffigures
    %    \fi
    %    \cleardoublepage
    %    \pagenumbering{arabic}
    %    \pagestyle{headings}
		\let\thesection=\oldthesection
}


%%%ver \sectionmark