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
#include "axWindowTree.h"
#include "axWindow.h"
#include "axApp.h"
#include "axCore.h"
//#include "axMath.h"
#include <axGL/axGLMath.h>
#include "axConfig.h"

axWindowNode::axWindowNode(axWindow* win)
{
    window = win;
}

axWindowNode::axWindowNode()
{
}

axWindowNode::~axWindowNode()
{
    for(axWindowNode* node : _childNodes)
    {
        if(node != nullptr)
        {
            delete node;
            node = nullptr;
        }
    }
    _childNodes.clear();
    
    
    if(window != nullptr)
    {
        //        axPrint("Delete node with win id", window->GetId());
        delete window;
        window = nullptr;
    }
}


void axWindowNode::DeleteWindow(axWindow* win)
{
    
}

axWindow* axWindowNode::GetWindow()
{
    return window;
}

void axWindowNode::SetWindow(axWindow* win)
{
    window = win;
}

void axWindowNode::AddWindow(axWindow* win)
{
    _childNodes.push_back(new axWindowNode(win));
}

axWindowNode* axWindowNode::Get(axWindow* win)
{
    for (axWindowNode* it : _childNodes)
    {
        if (it->window == win)
        {
            return it;
        }
    }
    return nullptr;
}

std::vector<axWindowNode*>& axWindowNode::GetChild()
{
    return _childNodes;
}


void BeforeDrawing(axWindow* win)
{
//    if(win->IsBlockDrawing())
    if(win->HasProperty("BlockDrawing"))
    {
        ax::GL::Math::Matrix4 mview;
        mview.Identity().Load();
        
        ax::Rect abs_rect = win->GetAbsoluteRect();
        ax::Rect shown_rect = win->GetShownRect();
        
//        double delta_size_x = shown_rect.size.x - abs_rect.size.x;
        double delta_size_y = shown_rect.size.y - abs_rect.size.y;
        
        double globalY = win->GetApp()->GetCore()->GetGlobalSize().y;
        double sumY = (abs_rect.position.y + shown_rect.position.y +
                       abs_rect.size.y + delta_size_y);
        
        glScissor(GLint(abs_rect.position.x + shown_rect.position.x),
                  GLint(globalY - sumY),
                  GLint(shown_rect.size.x + 1),
                  GLint(shown_rect.size.y));
        
        glEnable(GL_SCISSOR_TEST);
    }
}

void EndDrawing(axWindow* win)
{
//    if(win->IsBlockDrawing())
    if(win->HasProperty("BlockDrawing"))
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

void DrawWindow(axWindow* win)
{
    ax::GL::Math::Matrix4 mview;
    mview.Identity().Load();
    
    mview.Translate(win->GetAbsoluteRect().position -
                    win->GetScrollDecay()).Process();
    
    win->RenderWindow();
}


void axWindowNode::DrawNode()
{
    
    bool debug_active = window->GetApp()->IsDebugEditorActive();
    
    // Don't draw if not shown.
    if(!window->IsShown())
    {
        return;
    }
    
//    if(window->IsEditingWidget() && debug_active == false)
    if(window->HasProperty("EditingWidget") && debug_active == false)
    {
        // Don't draw debug editor window and childs.
        return;
    }

    ax::GL::Math::Matrix4 mview_before(GL_MODELVIEW_MATRIX);
    
    BeforeDrawing(window);
    DrawWindow(window);
    
    for(axWindowNode* it : _childNodes)
    {
        if(it->window == nullptr)
        {
            continue;
        }
        
//        bool is_edit_widget = it->window->IsEditingWidget();
        bool is_edit_widget = it->window->HasProperty("EditingWidget");
        //axPrint("axWindowNode::DrawNode  id : ", it->window->GetId());
        
        if(!it->window->IsShown())
        {
            continue;
        }
        
//        if(is_edit_widget && (!debug_active || !window->IsEditable()))
        if(is_edit_widget && (!debug_active || !window->HasProperty("Editable")))
        {
            continue;
        }
        
        // Save matrix.
        ax::GL::Math::Matrix4 mview_child_before(GL_MODELVIEW_MATRIX);
        
        // Block the drawging rectangle if window IsBlockDrawing activated.
        BeforeDrawing(it->window);
        
        DrawWindow(it->window);
        it->DrawNode();
        
        ax::GL::Math::Matrix4 mview;
        mview.Identity().Load();
        mview.Translate(it->window->GetAbsoluteRect().position).Process();
        
        // @todo This should be remove.
        it->window->OnPaintStatic();
        
        // Unblock rectangle.
        EndDrawing(it->window);
        
        // Reload original matrix.
        mview_child_before.Load();
    }

    EndDrawing(window);
}

void axWindowNode::ResizeNode(const ax::Size& size)
{
    
    window->OnResize(size);
    
    for(axWindowNode* it : _childNodes)
    {
        if(it->window == nullptr)
        {
            continue;
        }
        
        it->ResizeNode(window->GetSize());
//        it->window->OnResize(size);
    }

}


/*******************************************************************************
 * axWindowTree.
 ******************************************************************************/
axWindowTree::axWindowTree()
{
}

axWindowTree::~axWindowTree()
{
    for (auto& node : _nodes)
    {
        delete node;
    }
}

std::deque<axWindow*> axWindowTree::GetWindowParents(axWindow* win)
{
    std::deque<axWindow*> windows;
    
    while_not_null(win->GetParent())
    {
        win = win->GetParent();
        windows.push_front(win);
    }
    
    return windows;
}

axWindowNode* axWindowTree::FindWinNode(axWindow* win)
{
    std::deque<axWindow*> windows = GetWindowParents(win);
    
    if (windows.size() == 0)
    {
        return Get(win);
    }
    else
    {
        axWindowNode* parent = nullptr;
        
        // Find parent node.
        if_not_null(parent = Get(windows[0]))
        {
            windows.pop_front();
            
            for (axWindow* it : windows)
            {
                parent = parent->Get(it);
                if (parent == nullptr)
                {
                    return nullptr;
                }
            }
            
            if(parent == nullptr)
            {
                return nullptr;
            }
            return parent->Get(win);
        }
        
        // Didn't find the window.
        return nullptr;
    }
}

void axWindowTree::AddWindow(axWindow* win)
{
    if(win != nullptr)
    {
        std::deque<axWindow*> windows = GetWindowParents(win);
        
        // If there's no node in the nodes vector
        // then it must be the first one to be added
        // with nullptr parent.
        if (_nodes.size() == 0 && windows.size() == 0)
        {
            // First top level window.
            _nodes.push_back(new axWindowNode(win));
        }
        else if (windows.size() == 0)
        {
            // Second or more top level windows.
            _nodes.push_back(new axWindowNode(win));
        }
        else
        {
            axWindowNode* node = FindWinNode(win->GetParent());
            if_not_null(node)
            {
                node->AddWindow(win);
            }
        }
    }
}

void axWindowTree::DeleteWindow(axWindow* win)
{
    // Node to delete.
    axWindowNode* node = FindWinNode(win);
    
    if(node != nullptr)
    {
        // Find parent node.
        axWindowNode* parent = FindWinNode(node->window->GetParent());
        
        if(parent != nullptr)
        {
            // Vector of childs containing node to delete.
            std::vector<axWindowNode*>& childs = parent->GetChild();
            
            int id_to_delete = node->window->GetId();
            
            // Remove node from parent vector.
            childs.erase(std::remove_if(childs.begin(), childs.end(),
                                        [id_to_delete](axWindowNode* n)
                                        {
                                            return n->window->GetId() == id_to_delete;
                                        }),
                         childs.end());
        }
        
        delete node;
        node = nullptr;
    }
    else
    {
        ax::Print("axWindowTree::DeleteWindow :: Node is nullptr");
    }
    
}

std::vector<axWindowNode*> axWindowTree::GetMainNode()
{
    return _nodes;
}

axWindowNode* axWindowTree::Get(axWindow* win)
{
    for (axWindowNode* it : _nodes)
    {
        if (it->window == win)
        {
            return it;
        }
    }
    return nullptr;
}

axWindow* axWindowTree::FindMousePosition(const ax::Point& pos)
{
    axWindowNode* node = nullptr;
    
    // Find first level window.
    for (axWindowNode* it : _nodes)
    {
        ax::Point position = it->window->GetAbsoluteRect().position;
        ax::Rect rect(position, it->window->GetShownRect().size);
        if(rect.IsPointInside(pos))
        {
            node = it;
        }
        //		if (it->window->GetAbsoluteRect().IsPointInside(pos))
        //		{
        //			node = it;
        //		}
    }
    
    axWindowNode* n = node;
    
    //    axWindowNode* tmpNode = nullptr;
    
    if_not_null(n)
    {
        do
        {
            n = node;
            for (axWindowNode* it : n->GetChild())
            {
                ax::Point position = it->window->GetAbsoluteRect().position;
                ax::Rect rect(position, it->window->GetShownRect().size);
                
                if (rect.IsPointInside(pos) && it->window->IsShown())
                {
//                    if(it->window->IsSelectable())
                    if(it->window->HasProperty("Selectable"))
                    {
                        node = it;
                        break;
                    }
                    else
                    {
                        // If not selectable, look for Editing widget.
                        // For now, the debug edition button can only be on the
                        // first layer of childs of an unselectable widget.
                        for(axWindowNode* k : it->GetChild())
                        {
                            axWindow* win = k->window;
                            ax::Point p = win->GetAbsoluteRect().position;
                            ax::Rect r(p, win->GetShownRect().size);
                            
                            if(r.IsPointInside(pos) &&
                               win->HasProperty("EditingWidget"))
                            {
                                node = k;
                                break;
                            }
                        }
                    }
                }
            }
            
        } while (n != node);
    }
    
    if(node != nullptr && node->window->IsShown())
    {
        return node->window;
    }
    
    return nullptr;
}

void axWindowTree::DrawTree()
{
    for (axWindowNode* it : _nodes)
    {
        if(it != nullptr)
        {
            it->DrawNode();
        }
    }
}