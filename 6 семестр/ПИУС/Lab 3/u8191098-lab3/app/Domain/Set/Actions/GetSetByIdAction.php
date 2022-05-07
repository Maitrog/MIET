<?php

namespace App\Domain\Set\Actions;

use App\Models\Set;

class GetSetByIdAction
{
    public function execute(int $setId) :Set
    {
        return Set::findOrFail($setId);
    }
}
