<?php

namespace App\Domain\Set\Actions;

use App\Models\Set;

class GetAllSetAction
{
    public function execute() : array
    {
        return Set::all()->toArray();
    }
}
