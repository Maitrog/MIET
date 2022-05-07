<?php

namespace App\Http\ApiV1\Requests\MuscleGroupRequests;

use Illuminate\Foundation\Http\FormRequest;

class CreateMuscleGroupRequest extends FormRequest
{
    public function rules(): array
    {
        return [
            'name' => 'required|unique:muscle_groups,name|max:255',
        ];
    }
}
