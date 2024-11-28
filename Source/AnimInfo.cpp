#include "pch.h"
#include "AnimInfo.h"

void AnimInfo::CreateAnimation()
{
    if (animation.isNotNull())
        return;

    auto spritecache = ax::SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile(strPlist);

    ax::Vector<ax::SpriteFrame*> animFrames;
    char str[128];
    if (frameCount > 1)
    {
        int end = startFrame + frameCount;
        for (int i = startFrame; i < end; i++)
        {
            sprintf(str, format, i);
            ax::SpriteFrame* sp = spritecache->getSpriteFrameByName(str);
            sp->setAnchorPoint(anchor);
            animFrames.pushBack(sp);
        }
    }
    else
    {
        sprintf(str, format, startFrame);
        ax::SpriteFrame* sp = spritecache->getSpriteFrameByName(str);
        sp->setAnchorPoint(anchor);
        animFrames.pushBack(sp);
        animFrames.pushBack(sp);
    }
    animation = ax::Animation::createWithSpriteFrames(animFrames,perFrameTime);
}

