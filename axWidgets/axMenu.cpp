/*******************************************************************************
 * Copyright (c) 2013 Alexandre Arsenault.
 *
 * This file is part of axLibrary.
 *
 * axLibrary is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axLibrary License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLibrary. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLibrary, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 ******************************************************************************/
#include "axMenu.h"


/********************************************************************************//**
* axMenuNode.
***********************************************************************************/
axMenuNode::axMenuNode( axWindow* parent,
                        const ax::Rect& rect):
                        axPanel(parent, rect),
                        // Members.
                        m_label("ROOT"),
                        m_img(nullptr),
                        m_nCurrentImg( axMENU_NODE_IMAGE_SELECTED ),
                        m_select_mode( axMENU_SELECT_ANY )
{
    m_parentNode = NULL;

    m_nSubNode = 0;
    m_nSubNodeMax = axMENU_NODE_INIT_ARRAY_SIZE;
    //m_nodes = new_ axMenuNode* [ m_nSubNodeMax ];

    m_delta = -8;

    // Set default node size.
    SetSize(ax::Size(rect.size.x, axMENU_NODE_HEIGHT));
}

axMenuNode::axMenuNode(axMenuNode* parent,
                       const std::string& label,
                       std::string img_path,
                       axMenuNodeSelectionMode mode ):
// Heritage.
axPanel(parent, ax::Rect(0, 0, 20, 20)),
// Members.
m_parentNode(parent),
m_label(label),
m_nCurrentImg(axMENU_NODE_IMAGE_NORMAL),
m_nSubNode(0),
m_nSubNodeMax(axMENU_NODE_INIT_ARRAY_SIZE)
{
    //m_nodes = new_ axMenuNode* [ m_nSubNodeMax ];
    m_delta = parent->GetDelta() + 8;

	m_img = new_ ax::Image(img_path);
}

void axMenuNode::AddSubNode(axMenuNode* node)
{
    if( node )
    {
        // Resize node to parent size.
        node->SetSize(ax::Size(GetParent()->GetSize().x, axMENU_NODE_HEIGHT));

        // If is not the fisrt one to be added.
        if(_nodes.size())
        {
            node->SetPosition(_nodes[_nodes.size()-1]->GetButtomPosition());
        }
        // First added.
        else 
        {
            node->SetPosition(ax::Point(0, axMENU_NODE_HEIGHT));
        }

        // Add Node.
        _nodes.push_back(node);

        ResizeNode();
    }
}

void axMenuNode::ResizeNode()
{
    int y = axMENU_NODE_HEIGHT;

    if(_nodes.size() && m_nCurrentImg == axMENU_NODE_IMAGE_SELECTED)
    {
        for(auto n : _nodes)
        {
            y += n->GetSize().y;
        }

        y -= (_nodes.size() + 1);

        for(int i = 1; i < _nodes.size(); ++i)
        {
            _nodes[i]->SetPosition(_nodes[i - 1]->GetButtomPosition() - ax::Point(0, 1));
        }

        for(auto n : _nodes)
        {
            std::cout << n->GetLabel() << std::endl;
            n->Show();
        }
    }

    else
    {
        for(auto n : _nodes)
        {
            n->Hide();
        }
    }

    SetSize(ax::Size(GetSize().x, y));

    if(m_parentNode) 
    {
        m_parentNode->ResizeNode();
    }
}

void axMenuNode::SelectNode()
{
    if( m_nCurrentImg == axMENU_NODE_IMAGE_NORMAL )
    {
        m_nCurrentImg = axMENU_NODE_IMAGE_SELECTED;

        ResizeNode();
        Update();
    }
}

ax::Point axMenuNode::GetButtomPosition()
{
    return ax::Point(GetRect().position.x, GetRect().position.y + GetRect().size.y + 1 );
}

void axMenuNode::UnselectAll()
{
}

void axMenuNode::OnMouseLeftDown(const ax::Point& pos)
{
    // If node is already selected.
    if( m_nCurrentImg == axMENU_NODE_IMAGE_SELECTED )
    {
        // Set node UI info to unselected.
        m_nCurrentImg = axMENU_NODE_IMAGE_NORMAL;
    }

    else // Node if unselected.
    {
        m_nCurrentImg = axMENU_NODE_IMAGE_SELECTED;
    }

    ResizeNode();
    Update();
}

void axMenuNode::OnPaint()
{
    ax::GC gcs;
    ax::GC* gc = &gcs;
    ax::Size size = GetSize();
    ax::Rect rect( m_delta, 0, size.x, axMENU_NODE_HEIGHT );
	ax::Rect rect0(0.0, 0.0, rect.size.x, rect.size.y);

    gc->SetColor(ax::Color(0.6, 0.6, 0.6));
    gc->DrawRectangle(rect0);

    gc->SetColor( ax::Color("#AAAAAA") );
    ax::Font font("FreeSans.ttf");
    font.SetFontSize(13);
//    gc->SetFontSize(13);

    //cout << "Rect : " << rect.position.x << " " << rect.position.y << " " << rect.size.x << " " << rect.size.y << endl;
    gc->DrawStringAlignedCenter(font, m_label, rect);

    if( m_img != nullptr && m_img->IsImageReady() )
    {
        gc->DrawPartOfImage(m_img,
                            ax::Point( 0, m_nCurrentImg * 12 ),
                            ax::Size( 12, 12 ), ax::Point(m_delta + 7, 4));
    }

    // Contour.
    gc->SetColor(ax::Color(0.0, 0.0, 0.0));
    gc->DrawRectangleContour(ax::Rect(0, 0, size.x, size.y));
}

/********************************************************************************//**
* axMenu.
***********************************************************************************/
axMenu::axMenu(axWindow* parent, const ax::Rect& rect):
               axPanel(parent, rect)
{
    m_root = NULL;
}

bool axMenu::AddRootNode(axMenuNode* node)
{
    // If root node doesn't already exist.
    if( !m_root )
    {
        // If scroll bar exist
        //if(scrollBar != NULL)
        //{
            // Resize new_ node added with scrollbar.
        //    node->SetSize(node->GetSize() + wxSize(GetSize().x - INIT_WIDTH - scrollBar->GetSize().x, 0));
        //}
        //else
        //{
            // Resize new_ node added.
            //node->SetSize(node->GetSize() + wxSize(GetSize().x - INIT_WIDTH, 0));
        //}

        node->SetSize(ax::Size(GetSize().x, 15));
        m_root = node;

        return 1;
    }

    else return 0;
}

void axMenu::OnPaint()
{
    ax::GC gcs = ax::GC();
    ax::GC* gc = &gcs;
    ax::Size size = GetSize();
    ax::Rect rect(GetRect());
    ax::Rect rect0(ax::Point(0, 0), rect.size);

    gc->SetColor( ax::Color("#444444") );
    gc->DrawRectangle(rect0);

    // Contour.
    gc->SetColor(ax::Color("#000000"));
    gc->DrawRectangleContour(ax::Rect(1, 1, rect0.size.x - 1, rect0.size.y - 1));
}

